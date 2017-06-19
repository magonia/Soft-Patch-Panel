#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <CUnit/Console.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

// テスト対象ソースインクルード
#include "../src/shared/ringlatencystats.c"

// =============================================================================
// 定数定義
// =============================================================================

// =============================================================================
// グローバル変数
// =============================================================================

// =============================================================================
// セットアップ処理
// =============================================================================
static int setup(void) {
//  spp_apl_log_initialize();
  return 0;
}

// =============================================================================
// ティアダウン処理
// =============================================================================
static int teardown(void) {
//  spp_apl_log_finalize();
  return 0;
}

// =============================================================================
// テストケース ringlatencystatics
// =============================================================================
/**
 * test for spp_ringlatencystats_init
 */
static void UT_ringlatencystats_01(void) {

  /* tests */
  CU_ASSERT_EQUAL(spp_ringlatencystats_init(1000, 10), 0);
  CU_ASSERT_EQUAL(spp_ringlatencystats_init(1000, 0), -1);

  /* cleanup */
  spp_ringlatencystats_uninit();
}

/**
 * test for spp_ringlatencystats_uninit
 */
 static void UT_ringlatencystats_02(void) {

   /* setup */
   spp_ringlatencystats_init(1000, 10);

   /* tests */
   CU_ASSERT_EQUAL(spp_ringlatencystats_uninit(), 0);
 }

 /**
  * test for spp_ringlatencystats_add_time_stamp
  */
static void UT_ringlatencystats_03(void) {

  int i, n;
  int n_ring = 10;
  int n_pkt = 64;
  int n_timestamp = 0;
  struct rte_mbuf mbufs[n_ring][n_pkt];
  struct rte_mbuf *pkts[n_pkt];

  /* setup */
  spp_ringlatencystats_init(1000, n_ring);

  /* tests */
  for (i = 0; i < n_ring; i++) {
    for (n = 0; n < n_pkt; n++) {
      pkts[n] = &mbufs[i][n];
      memset(pkts[n], 0, sizeof(struct rte_mbuf));
    }
    CU_ASSERT_EQUAL(
        spp_ringlatencystats_add_time_stamp(i, pkts, n_pkt), n_pkt);
  }

  /* check number of timestamps */
  for (i = 0; i < n_ring; i++) {
    for (n = 0; n < n_pkt; n++) {
      printf("%lu\n", mbufs[i][n].timestamp);
      if (mbufs[i][n].timestamp != 0)
        n_timestamp++;
    }
  }
  CU_ASSERT_NOT_EQUAL(n_timestamp, 0);

  CU_ASSERT_EQUAL(
      spp_ringlatencystats_add_time_stamp(0, NULL, 0), 0);

  /* cleanup */
  spp_ringlatencystats_uninit();
}

/**
 * test for spp_ringlatencystats_calculate_latency
 */
 static void UT_ringlatencystats_04(void) {

   int i, n;
   int n_ring = 1;
   int n_pkt = 32;
   int n_timestamp = 0;
   struct rte_mbuf mbufs[n_ring][n_pkt];
   struct rte_mbuf *pkts[n_pkt];
   struct spp_ringlatencystats_ring_latency_stats stats[n_ring];

   /* setup */
   spp_ringlatencystats_init(1000, n_ring);

   /* tests */
   for (i = 0; i < n_ring; i++) {
     for (n = 0; n < n_pkt; n++) {
       pkts[n] = &mbufs[i][n];
       memset(pkts[n], 0, sizeof(struct rte_mbuf));
     }
     spp_ringlatencystats_add_time_stamp(i, pkts, n_pkt);
   }

   for (i = 0; i < n_ring; i++) {
     CU_ASSERT_EQUAL(
         spp_ringlatencystats_calculate_latency(i, pkts, n_pkt), n_pkt);
   }

   CU_ASSERT_EQUAL(spp_ringlatencystats_get_count(), n_ring);

   for (i = 0; i < n_ring; i++) {
     spp_ringlatencystats_get_stats(i, &stats[i]);
     printf("stats:ring:%d\n", i);
     for (n = 0; n < SPP_RINGLATENCYSTATS_STATS_SLOT_COUNT; n++)
      printf("  %lu\n", stats[i].slot[n]);
   }

   CU_ASSERT_EQUAL(
       spp_ringlatencystats_calculate_latency(0, NULL, 0), 0);

   /* cleanup */
   spp_ringlatencystats_uninit();
 }

// =============================================================================
// Main処理　※．テストケースの呼び出しはここに追加して下さい
// =============================================================================
int main(int argc, char **argv) {
  CU_initialize_registry();
  // ※．テスト対象に応じてCU_add_suiteの引数は書き換えてください
  CU_pSuite suite = CU_add_suite("ringlatencystats_test", setup, teardown);

  rte_eal_timer_init();

  /**    ここにテストコードの呼び出しを追加してください      **/
  CU_ADD_TEST(suite, UT_ringlatencystats_01);
  CU_ADD_TEST(suite, UT_ringlatencystats_02);
  CU_ADD_TEST(suite, UT_ringlatencystats_03);
  CU_ADD_TEST(suite, UT_ringlatencystats_04);

  /**    ここにテストコードの呼び出しを追加してください      **/
  // "CU_BRM_VERBOSE:Test: test_xxxx ... passd"をコンソールに表示
  CU_basic_set_mode(CU_BRM_VERBOSE);
  if (argc == 1) {
    // ※．テスト対象に応じてCU_set_output_filenameの引数は書き換えてください
    CU_set_output_filename("ringlatencystats_test");
    CU_automated_run_tests();
  } else {
    if (strcmp(argv[1], "-b") == 0) { CU_basic_run_tests(); }
    if (strcmp(argv[1], "-c") == 0) { CU_console_run_tests(); }
  }
  const int failed = CU_get_number_of_failures();
  CU_cleanup_registry();
  return -failed;
}
