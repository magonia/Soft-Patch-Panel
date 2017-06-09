#ifndef _RINGLATENCYSTATS_H_
#define _RINGLATENCYSTATS_H_

#include <rte_mbuf.h>

/** number of slots to save latency. 0ns~99ns and 100ns over */
#define SPP_RINGLATENCYSTATS_STATS_SLOT_COUNT 101

/** ring latency ｓtatistics */
struct spp_ring_latency_stats {
	uint64_t slot[SPP_RINGLATENCYSTATS_STATS_SLOT_COUNT]; /**< slots to save latency */
};

/**
 * initialize ring latency statisics.
 *
 * @retval 0: succeeded.
 * @retval -1: failed.
 */
int spp_ringlatencystats_init(uint64_t samp_intvl, uint16_t stats_count);

/**
 *uninitialize ring latency statisics.
 */
int spp_ringlatencystats_uninit(void);

/**
 * add time-stamp to mbuf's member.
 *
 * call at enqueue.
 *
 * @retval 0: succeeded.
 */
int spp_ringlatencystats_add_time_stamp(int rind_id,
			struct rte_mbuf **pkts, uint16_t nb_pkts);

/**
 * calculate latency.
 *
 * call at dequeue.
 *
 * @retval 0: succeeded.
 */
int spp_ringlatencystats_calculate_latency(int ring_id,
			struct rte_mbuf **pkts, uint16_t nb_pkts);

/**
 * get number of ring latency statisics.
 *
 * @return spp_ringlatencystats_init's parameter "stats_count"
 */
int spp_ringlatencystats_get_count(void);

/**
 *get specific ring latency statisics.
 */
void spp_ringlatencystats_get_stats(int ring_id,
		struct spp_ring_latency_stats *stats);

#endif /* _RINGLATENCYSTATS_H_ */
