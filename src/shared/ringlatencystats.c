#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include <rte_mbuf.h>
#include <rte_log.h>
#include <rte_cycles.h>
#include <rte_malloc.h>
#include <rte_memcpy.h>

#include "ringlatencystats.h"

#define RTE_LOGTYPE_SPP_RING_LATENCY_STATS RTE_LOGTYPE_USER1

/** ring latency statistics information */
struct spp_ring_latency_stats_info {
	uint64_t timer_tsc;   /**< sampling interval counter */
	uint64_t prev_tsc;    /**< previous time */
	struct spp_ring_latency_stats stats;  /**< ring latency statistics list */
};

/** sampling interval */
static uint64_t g_samp_intvl = 0;

/** ring latency statistics information instance */
static struct spp_ring_latency_stats_info *g_stats_info = NULL;

/** number of ring latency statisics */
static uint16_t g_stats_count = 0;

/* clock cycles per nano second */
static uint64_t
cycles_per_ns(void)
{
	return rte_get_timer_hz() / 1E9;
}

int
spp_ringlatencystats_init(uint64_t samp_intvl, uint16_t stats_count)
{
	/* allocate memory for ring latency statisics infromation */
	g_stats_info = rte_zmalloc(
			"global spp_ring_latency_stats_info",
			sizeof(struct spp_ring_latency_stats_info) * stats_count, 0);
	if (g_stats_info == NULL) {
		RTE_LOG(ERR, SPP_RING_LATENCY_STATS,
				"Cannot allocate memory for ring latency stats info\n");
		return -1;
	}

	/* store global information for ring latency statistics */
	g_samp_intvl = samp_intvl * cycles_per_ns();
	g_stats_count = stats_count;

	RTE_LOG(DEBUG, SPP_RING_LATENCY_STATS,
			"g_samp_intvl=%lu, g_stats_count=%hu, cpns=%lu\n",
			g_samp_intvl, g_stats_count, cycles_per_ns());

	return 0;
}

int
spp_ringlatencystats_uninit(void)
{
	/* free memory for ring latency statisics infromation */
	if (g_stats_info != NULL) {
		rte_free(g_stats_info);
		g_stats_count = 0;
	}

	return 0;
}

int
spp_ringlatencystats_add_time_stamp(int ring_id,
			struct rte_mbuf **pkts, uint16_t nb_pkts)
{
	unsigned int i;
	uint64_t diff_tsc, now;
	struct spp_ring_latency_stats_info *stats_info = &g_stats_info[ring_id];

	now = rte_rdtsc();
	for (i = 0; i < nb_pkts; i++) {

		/* calculate difference from the previous processing time */
		diff_tsc = now - stats_info->prev_tsc;
		stats_info->timer_tsc += diff_tsc;

		/* when it is over sampling interval */
		/* set tsc to mbuf::timestamp */
		if (stats_info->timer_tsc >= g_samp_intvl) {
			pkts[i]->timestamp = now;
			stats_info->timer_tsc = 0;
		}

		/* update previus tsc, and now tsc */
		stats_info->prev_tsc = now;
		now = rte_rdtsc();
	}

	return nb_pkts;
}

int
spp_ringlatencystats_calculate_latency(int ring_id,
			struct rte_mbuf **pkts, uint16_t nb_pkts)
{
	unsigned int i;
	uint64_t now;
	int64_t latency;
	struct spp_ring_latency_stats_info *stats_info = &g_stats_info[ring_id];

	now = rte_rdtsc();
	for (i = 0; i < nb_pkts; i++) {
		if (pkts[i]->timestamp == 0)
			continue;

		/* when mbuf::timestamp is not zero */
		/* calculate latency */
		latency = (uint64_t)floor((now - pkts[i]->timestamp) / cycles_per_ns());
		if (latency < SPP_RINGLATENCYSTATS_STATS_SLOT_COUNT-1)
			stats_info->stats.slot[latency]++;
		else
			stats_info->stats.slot[SPP_RINGLATENCYSTATS_STATS_SLOT_COUNT-1]++;
	}

	return nb_pkts;
}

int
spp_ringlatencystats_get_count(void)
{
	return g_stats_count;
}

void
spp_ringlatencystats_get_stats(int ring_id,
		struct spp_ring_latency_stats *stats)
{
	struct spp_ring_latency_stats_info *stats_info = &g_stats_info[ring_id];

	rte_memcpy(stats, &stats_info->stats,
			sizeof(struct spp_ring_latency_stats));
}
