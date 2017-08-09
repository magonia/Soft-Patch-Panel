#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "common.h"
#include "spp_vf.h"
#include "ringlatencystats.h"

char stub_config_file_name[256];
__thread __typeof__(unsigned) per_lcore__lcore_id;
int stub_dpdk_port_id = 0;

// =============================================================================
// stub関数
// =============================================================================
int spp_classifier_mac_do(void *arg)
{
	return 0;
}
int stub_ret_spp_ringlatencystats_init = 0;
int spp_ringlatencystats_init(uint64_t samp_intvl, uint16_t stats_count)
{
	return stub_ret_spp_ringlatencystats_init;
}
void spp_ringlatencystats_uninit()
{
	return;
}
void spp_ringlatencystats_get_stats(int ring_id,
                struct spp_ringlatencystats_ring_latency_stats *stats)
{
	return;
}

int spp_forward(void *arg)
{
	return 0;
}

int stub_ret_spp_classifier_mac_update = 0;
int spp_classifier_mac_update(struct spp_core_info *core_info)
{
	printf("spp_classifier_mac_update\n");
	return stub_ret_spp_classifier_mac_update;
}

int spp_command_proc_init(const char* controller_ip, int controller_port)
{
	return 0;
}

void spp_command_proc_do(void)
{
	return;
}
// =============================================================================
// DPDK関連 stub関数
// =============================================================================
int stub_ret_rte_ring_lookup = 0;
static struct rte_ring stub_rte_ring_lookup;
struct rte_ring *rte_ring_lookup(const char *name)
{
	if (stub_ret_rte_ring_lookup != 0) {
		return NULL;
	}
	return &stub_rte_ring_lookup;
}

int stub_ret_rte_eth_from_ring = 0;
int rte_eth_from_ring(struct rte_ring *r)
{
	if (stub_ret_rte_eth_from_ring > 0) {
		stub_ret_rte_eth_from_ring++;
	}
	return stub_ret_rte_eth_from_ring;
}

int stub_ret_rte_mempool_lookup = 0;
static struct rte_mempool stub_rte_mempool_lookup;
struct rte_mempool *rte_mempool_lookup(const char *name)
{
	if (stub_ret_rte_mempool_lookup != 0) {
		return NULL;
	}
	return &stub_rte_mempool_lookup;
}

int stub_ret_rte_eth_dev_attach = 0;
int rte_eth_dev_attach(const char *devargs, uint8_t *port_id)
{
	stub_dpdk_port_id++;
	*port_id = stub_dpdk_port_id;
	return stub_ret_rte_eth_dev_attach;
}

int stub_ret_rte_eth_dev_configure = 0;
int rte_eth_dev_configure(uint8_t port_id, uint16_t nb_rx_q, uint16_t nb_tx_q,
                          const struct rte_eth_conf *dev_conf)
{
	return stub_ret_rte_eth_dev_configure;
}

int rte_eth_dev_socket_id(uint8_t port_id)
{
	return 0;
}

int stub_ret_rte_eth_rx_queue_setup = 0;
int rte_eth_rx_queue_setup(uint8_t port_id, uint16_t rx_queue_id,
                       uint16_t nb_rx_desc, unsigned int socket_id,
                       const struct rte_eth_rxconf *rx_conf,
                       struct rte_mempool *mp)
{
	return stub_ret_rte_eth_rx_queue_setup;
}

int stub_ret_rte_eth_tx_queue_setup = 0;
int rte_eth_tx_queue_setup(uint8_t port_id, uint16_t tx_queue_id,
                           uint16_t nb_tx_desc, unsigned int socket_id,
                           const struct rte_eth_txconf *tx_conf)
{
	return stub_ret_rte_eth_tx_queue_setup;
}

int stub_ret_rte_eth_dev_start = 0;
int rte_eth_dev_start(uint8_t port_id)
{
	return stub_ret_rte_eth_dev_start;
}

uint8_t rte_eth_dev_count(void)
{
	return 2;
}

int stub_ret_rte_eal_init = 0;
int rte_eal_init(int argc, char ** argv) {
	return stub_ret_rte_eal_init;
}

int stub_status_rte_eal_remote_launch = SPP_CORE_IDLE;
int rte_eal_remote_launch(int (*f)(void *), void *arg, unsigned slave_id) {
	struct spp_core_info *core = (struct spp_core_info*)arg;
	core->status = stub_status_rte_eal_remote_launch;
	return 0;
}

static struct rte_config stub_rte_config;
struct rte_config *rte_eal_get_configuration(void)
{
        return &stub_rte_config;
}

void rte_log_set_global_level(uint32_t level)
{
	return;
}
