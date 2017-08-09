#pragma once

#include "spp_vf.h"
#include <stdarg.h>

#undef SPP_CONFIG_FILE_PATH
extern char stub_config_file_name[256];
#define SPP_CONFIG_FILE_PATH stub_config_file_name

#undef RTE_LOG
#ifdef CUNIT_LOG_FLG
#define RTE_LOG(l, t, fmt, ...) do{}while(0);
#else
#define STUB_RTE_LOG(l, t, fmt, ...) \
if(strcmp(# l, "DEBUG") != 0 )       \
{                                    \
  printf("%-8s:%-12s:", # l, # t);   \
  printf(fmt"%s", __VA_ARGS__);      \
}
#define RTE_LOG(...) STUB_RTE_LOG(__VA_ARGS__, "")
#endif

#undef RTE_LCORE_FOREACH_SLAVE
#define RTE_LCORE_FOREACH_SLAVE(i) for (i = 0; i < 32; i++)

extern int stub_ret_spp_classifier_mac_update;

extern int stub_ret_rte_ring_lookup;
extern int stub_ret_rte_eth_from_ring;
extern int stub_ret_rte_mempool_lookup;
extern int stub_ret_rte_eth_dev_attach;
extern int stub_ret_rte_eth_dev_configure;
extern int stub_ret_rte_eth_rx_queue_setup;
extern int stub_ret_rte_eth_tx_queue_setup;
extern int stub_ret_rte_eth_dev_start;
extern int stub_dpdk_port_id;
extern int stub_ret_rte_eal_init;
extern int stub_ret_spp_ringlatencystats_init;
extern int stub_status_rte_eal_remote_launch;

int classifier_mac(void *arg);
