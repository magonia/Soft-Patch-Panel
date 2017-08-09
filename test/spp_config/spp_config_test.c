#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <CUnit/Console.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "stub.h"
// テスト対象ソースインクルード
#include "../vf/spp_config.c"

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
  return 0;
}

// =============================================================================
// ティアダウン処理
// =============================================================================
static int teardown(void) {
  return 0;
}

// =============================================================================
// テストケース01 config_get_int_value
// =============================================================================
// TEST01：正常終了
static void UT_config_get_int_value_01(void) {
  int ret = -1;
  int out = 0;
  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_get_int_value(obj, "$.vfs[0].num_vhost", &out);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(out, 3);
}

// TEST02：パラメータなし
static void UT_config_get_int_value_02(void) {
  int ret = 0;
  int out = 0;
  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_get_int_value(obj, "$.vfs[0].num_vhos", &out);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
  CU_ASSERT_EQUAL(out, 0);
}

// TEST03：型不一致
static void UT_config_get_int_value_03(void) {
  int ret = 0;
  int out = 0;
  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_get_int_value(obj, "$.vfs[0].name", &out);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
  CU_ASSERT_EQUAL(out, 0);
}

// =============================================================================
// テストケース02 config_get_str_value
// =============================================================================
// TEST01：正常終了
static void UT_config_get_str_value_01(void) {
  int ret = -1;
  char out_str[64];
  memset(out_str, 0x00, 64);

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_get_str_value(obj, "$.vfs[0].name", out_str);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_STRING_EQUAL(out_str, "vf0");
}

// TEST02：パラメータなし
static void UT_config_get_str_value_02(void) {
  int ret = -1;
  char out_str[64];
  memset(out_str, 0x00, 64);

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_get_str_value(obj, "$.vfs[0].name", out_str);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_STRING_EQUAL(out_str, "vf0");
}

// TEST03：型不一致
static void UT_config_get_str_value_03(void) {
  int ret = -1;
  char out_str[64];
  memset(out_str, 0x00, 64);

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_get_str_value(obj, "$.vfs[0].name", out_str);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_STRING_EQUAL(out_str, "vf0");
}

// =============================================================================
// テストケース03 config_init_data
// =============================================================================
// TEST01：正常終了
static void UT_config_init_data_01(void) {
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験関数起動 */
  config_init_data(&config);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(config.proc.functions[0].rx_ports[0].if_type, UNDEF);
  CU_ASSERT_EQUAL(config.proc.functions[1].tx_ports[1].if_type, UNDEF);
  CU_ASSERT_EQUAL(config.classifier_table.mac_tables[0].port.if_type, UNDEF);
}

// =============================================================================
// テストケース04 spp_config_get_if_info
// =============================================================================
// TEST01：正常終了(NIC)
static void UT_spp_config_get_if_info_01(void) {
  int ret = -1;
  enum port_type if_type = -1;
  int if_no = -1;

  /* 試験関数起動 */
  ret = spp_config_get_if_info("nic0", &if_type, &if_no);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(if_type, 0);
  CU_ASSERT_EQUAL(if_no, 0);
}

// TEST02：正常終了(VHOST)
static void UT_spp_config_get_if_info_02(void) {
  int ret = -1;
  enum port_type if_type = -1;
  int if_no = -1;

  /* 試験関数起動 */
  ret = spp_config_get_if_info("vhost5", &if_type, &if_no);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(if_type, 2);
  CU_ASSERT_EQUAL(if_no, 5);
}

// TEST03：正常終了(RING)
static void UT_spp_config_get_if_info_03(void) {
  int ret = -1;
  enum port_type if_type = -1;
  int if_no = -1;

  /* 試験関数起動 */
  ret = spp_config_get_if_info("ring7", &if_type, &if_no);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(if_type, 1);
  CU_ASSERT_EQUAL(if_no, 7);
}

// TEST04：IF種別異常
static void UT_spp_config_get_if_info_04(void) {
  int ret = -1;
  enum port_type if_type = -1;
  int if_no = -1;

  /* 試験関数起動 */
  ret = spp_config_get_if_info("7777", &if_type, &if_no);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
  CU_ASSERT_EQUAL(if_type, -1);
  CU_ASSERT_EQUAL(if_no, -1);
}

// TEST05：IF番号なし
static void UT_spp_config_get_if_info_05(void) {
  int ret = -1;
  enum port_type if_type = -1;
  int if_no = -1;

  /* 試験関数起動 */
  ret = spp_config_get_if_info("nic", &if_type, &if_no);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
  CU_ASSERT_EQUAL(if_type, -1);
  CU_ASSERT_EQUAL(if_no, -1);
}

// TEST06：IF番号異常
static void UT_spp_config_get_if_info_06(void) {
  int ret = -1;
  enum port_type if_type = -1;
  int if_no = -1;

  /* 試験関数起動 */
  ret = spp_config_get_if_info("ringNG", &if_type, &if_no);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
  CU_ASSERT_EQUAL(if_type, -1);
  CU_ASSERT_EQUAL(if_no, -1);
}

// =============================================================================
// テストケース05 spp_config_change_mac_str_to_int64
// =============================================================================
// TEST01：正常終了
static void UT_spp_config_change_mac_str_to_int64_01(void) {
  int64_t ret = -1;

  /* 試験関数起動 */
  ret = spp_config_change_mac_str_to_int64("AA:BB:CC:DD:EE:FF");

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0x0000ffeeddccbbaa);
}

// TEST02：16進数値以外の文字列あり
static void UT_spp_config_change_mac_str_to_int64_02(void) {
  int64_t ret = -1;

  /* 試験関数起動 */
  ret = spp_config_change_mac_str_to_int64("AA:II:CC:DD:EE:FF");

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST03：コロンで終了
static void UT_spp_config_change_mac_str_to_int64_03(void) {
  int64_t ret = -1;

  /* 試験関数起動 */
  ret = spp_config_change_mac_str_to_int64("AA:BB:CC:DD:EE:");

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// =============================================================================
// テストケース06 config_load_classifier_table
// =============================================================================
// TEST01：正常終了
static void UT_config_load_classifier_table_01(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_STRING_EQUAL(classifier_table.name, "classifier_mac_table");
  CU_ASSERT_EQUAL(classifier_table.num_table, 3);
  CU_ASSERT_EQUAL(classifier_table.mac_tables[0].port.if_type, 1);
  CU_ASSERT_EQUAL(classifier_table.mac_tables[0].port.if_no, 0);
  CU_ASSERT_STRING_EQUAL(classifier_table.mac_tables[0].mac_addr_str, "32:61:3C:4E:B6:05");
  CU_ASSERT_EQUAL(classifier_table.mac_tables[0].mac_addr, 0x000005B64E3C6132);

  CU_ASSERT_EQUAL(classifier_table.mac_tables[1].port.if_type, 1);
  CU_ASSERT_EQUAL(classifier_table.mac_tables[1].port.if_no, 1);
  CU_ASSERT_STRING_EQUAL(classifier_table.mac_tables[1].mac_addr_str, "32:61:3C:4E:B6:06");
  CU_ASSERT_EQUAL(classifier_table.mac_tables[1].mac_addr, 0x000006B64E3C6132);

  CU_ASSERT_EQUAL(classifier_table.mac_tables[2].port.if_type, 1);
  CU_ASSERT_EQUAL(classifier_table.mac_tables[2].port.if_no, 2);
  CU_ASSERT_STRING_EQUAL(classifier_table.mac_tables[2].mac_addr_str, "32:61:3C:4E:B6:07");
  CU_ASSERT_EQUAL(classifier_table.mac_tables[2].mac_addr, 0x000007B64E3C6132);
}

// TEST02：classifier_tableパラメータなし
static void UT_config_load_classifier_table_02(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-2_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
}

// TEST03：nameパラメータなし
static void UT_config_load_classifier_table_03(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-3_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST04：tableパラメータなし
static void UT_config_load_classifier_table_04(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-4_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST05：tableパラメータが配列以外
static void UT_config_load_classifier_table_05(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-5_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST06：tableパラメータの要素数の上限超え
static void UT_config_load_classifier_table_06(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-6_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST07：tableパラメータが要素取得失敗 ※発生不可
//static void UT_config_load_classifier_table_07(void) {
//  int ret = -1;
//  struct spp_config_classifier_table classifier_table;
//  memset(&classifier_table, 0x00, sizeof(classifier_table));
//
//  /* 試験用コンフィグ指定 */
//  strcpy(stub_config_file_name, "spp_config/6-7_vf.json");
//
//  /* Config load */
//  json_error_t json_error;
//  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
//  if (obj != NULL) {
//    /* 試験関数起動 */
//    ret = config_load_classifier_table(obj, &classifier_table);
//  }
//
//  /* 確認ポイントチェック */
//  CU_ASSERT_EQUAL(ret, -1);
//}

// TEST08：macパラメータ取得失敗
static void UT_config_load_classifier_table_08(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-8_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST09：MACアドレス変換失敗
static void UT_config_load_classifier_table_09(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-9_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST10：portパラメータ取得失敗
static void UT_config_load_classifier_table_10(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-10_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST11：IF情報の分割失敗
static void UT_config_load_classifier_table_11(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-11_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST12：tableパラメータの要素数の下限未満
static void UT_config_load_classifier_table_12(void) {
  int ret = -1;
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/6-12_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_classifier_table(obj, &classifier_table);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// =============================================================================
// テストケース07 config_change_core_type
// =============================================================================
// TEST01：正常終了(classifier)
static void UT_config_change_core_type_01(void) {
  int ret = -1;

  /* 試験関数起動 */
  ret = config_change_core_type("classifier_mac");

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 1);
}

// TEST02：正常終了(merge)
static void UT_config_change_core_type_02(void) {
  int ret = -1;

  /* 試験関数起動 */
  ret = config_change_core_type("merge");

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 2);
}

// TEST03：正常終了(forward)
static void UT_config_change_core_type_03(void) {
  int ret = -1;

  /* 試験関数起動 */
  ret = config_change_core_type("forward");

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 3);
}

// TEST04：知らない種別
static void UT_config_change_core_type_04(void) {
  int ret = -1;

  /* 試験関数起動 */
  ret = config_change_core_type("unknown");

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
}

// =============================================================================
// テストケース08 config_set_rx_port
// =============================================================================
// TEST01：正常終了(merge)
static void UT_config_set_rx_port_01(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_MERGE, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions.num_rx_port, 3);
  CU_ASSERT_EQUAL(functions.rx_ports[0].if_type, 1);
  CU_ASSERT_EQUAL(functions.rx_ports[0].if_no, 3);
  CU_ASSERT_EQUAL(functions.rx_ports[1].if_type, 1);
  CU_ASSERT_EQUAL(functions.rx_ports[1].if_no, 4);
  CU_ASSERT_EQUAL(functions.rx_ports[2].if_type, 1);
  CU_ASSERT_EQUAL(functions.rx_ports[2].if_no, 5);
}

// TEST02：正常終了(classifier)
static void UT_config_set_rx_port_02(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions.num_rx_port, 1);
  CU_ASSERT_EQUAL(functions.rx_ports[0].if_type, 0);
  CU_ASSERT_EQUAL(functions.rx_ports[0].if_no, 0);
}

// TEST02：正常終了(forward)
static void UT_config_set_rx_port_03(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[5]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_FORWARD, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions.num_rx_port, 1);
  CU_ASSERT_EQUAL(functions.rx_ports[0].if_type, 2);
  CU_ASSERT_EQUAL(functions.rx_ports[0].if_no, 1);
}

// TEST04：rx_port取得失敗
static void UT_config_set_rx_port_04(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-4_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_MERGE, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
 CU_ASSERT_EQUAL(ret, -1);
}

// TEST05：rx_portが配列型以外
static void UT_config_set_rx_port_05(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-5_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_MERGE, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST06：rx_portの要素数が下限未満
static void UT_config_set_rx_port_06(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-6_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_MERGE, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST07：rx_portの要素数が上限越え
static void UT_config_set_rx_port_07(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-7_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_MERGE, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST08：rx_portの要素が文字列以外
static void UT_config_set_rx_port_08(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-8_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_MERGE, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST09：rx_portの要素の分割失敗
static void UT_config_set_rx_port_09(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-9_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_MERGE, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST10：rx_port取得失敗(Merge以外)
static void UT_config_set_rx_port_10(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-10_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST11：rx_portのIF情報分割失敗(Merge以外)
static void UT_config_set_rx_port_11(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/8-11_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[0]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_rx_port(SPP_CONFIG_FORWARD, functions_obj, &functions);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// =============================================================================
// テストケース09 config_set_tx_port
// =============================================================================
// TEST01：正常終了(Merge)
static void UT_config_set_tx_port_01(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(struct spp_config_classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_MERGE, functions_obj, &functions, &classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions.num_tx_port, 1);
  CU_ASSERT_EQUAL(functions.tx_ports[0].if_type, 0);
  CU_ASSERT_EQUAL(functions.tx_ports[0].if_no, 0);
}

// TEST02：正常終了(Forward)
static void UT_config_set_tx_port_02(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(struct spp_config_classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[2]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_FORWARD, functions_obj, &functions, &classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions.num_tx_port, 1);
  CU_ASSERT_EQUAL(functions.tx_ports[0].if_type, 2);
  CU_ASSERT_EQUAL(functions.tx_ports[0].if_no, 2);
}

// TEST03：正常終了(Classifier Table名称指定)
static void UT_config_set_tx_port_03(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions->num_tx_port, 3);
  CU_ASSERT_EQUAL(functions->tx_ports[0].if_type, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[0].if_no, 0);
  CU_ASSERT_EQUAL(functions->tx_ports[1].if_type, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[1].if_no, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[2].if_type, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[2].if_no, 2);
  CU_ASSERT_EQUAL(functions->tx_ports[3].if_type, 3);
  CU_ASSERT_EQUAL(functions->tx_ports[3].if_no, 0);
}

// TEST04：tx_port取得失敗
static void UT_config_set_tx_port_04(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(struct spp_config_classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-4_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[7]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_MERGE, functions_obj, &functions, &classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST05：tx_portのIF情報分割失敗
static void UT_config_set_tx_port_05(void) {
  int ret = -1;
  struct spp_config_functions functions;
  memset(&functions, 0x00, sizeof(struct spp_config_functions));
  struct spp_config_classifier_table classifier_table;
  memset(&classifier_table, 0x00, sizeof(struct spp_config_classifier_table));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-5_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[6]");
    if (functions_obj != NULL) {
      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_FORWARD, functions_obj, &functions, &classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST06：正常終了(Classifier ポート指定) Classifier_tableあり
static void UT_config_set_tx_port_06(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-6_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions->num_tx_port, 2);
  CU_ASSERT_EQUAL(functions->tx_ports[0].if_type, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[0].if_no, 0);
  CU_ASSERT_EQUAL(functions->tx_ports[1].if_type, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[1].if_no, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[2].if_type, 3);
  CU_ASSERT_EQUAL(functions->tx_ports[2].if_no, 0);
}

// TEST07：正常終了(Classifier ポート指定) Classifier_tableなし
static void UT_config_set_tx_port_07(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-7_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_EQUAL(functions->num_tx_port, 2);
  CU_ASSERT_EQUAL(functions->tx_ports[0].if_type, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[0].if_no, 0);
  CU_ASSERT_EQUAL(functions->tx_ports[1].if_type, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[1].if_no, 1);
  CU_ASSERT_EQUAL(functions->tx_ports[2].if_type, 3);
  CU_ASSERT_EQUAL(functions->tx_ports[2].if_no, 0);
}

// TEST08：tx_port取得失敗
static void UT_config_set_tx_port_08(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-8_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST09：tx_portが配列以外
static void UT_config_set_tx_port_09(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-9_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST10：tx_portの要素数が下限未満
static void UT_config_set_tx_port_10(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-10_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST11：tx_portの要素数が上限越え
static void UT_config_set_tx_port_11(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-11_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST12：tx_portの要素が文字列以外
static void UT_config_set_tx_port_12(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-12_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST13：tx_portの要素の分割失敗
static void UT_config_set_tx_port_13(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));
  struct spp_config_functions *functions = &config.proc.functions[3];

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/9-13_vf.json");

  /* Config load */
  config_init_data(&config);
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    json_t *functions_obj = spp_config_get_path_obj(obj, "$.vfs[0].functions[3]");
    if (functions_obj != NULL) {
      config_load_classifier_table(obj, &config.classifier_table);

      /* 試験関数起動 */
      ret = config_set_tx_port(SPP_CONFIG_CLASSIFIER_MAC, functions_obj, functions, &config.classifier_table);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// =============================================================================
// テストケース10 config_load_proc_info
// =============================================================================
// TEST01：正常終了(Merge)
static void UT_config_load_proc_info_01(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_STRING_EQUAL(config.proc.name, "vf0");
  CU_ASSERT_EQUAL(config.proc.num_vhost, 3);
  CU_ASSERT_EQUAL(config.proc.num_ring, 6);
  CU_ASSERT_EQUAL(config.proc.functions[0].core_no, 1);
  CU_ASSERT_EQUAL(config.proc.functions[1].core_no, 2);
  CU_ASSERT_EQUAL(config.proc.functions[2].core_no, 3);
  CU_ASSERT_EQUAL(config.proc.functions[3].core_no, 4);
  CU_ASSERT_EQUAL(config.proc.functions[4].core_no, 5);
  CU_ASSERT_EQUAL(config.proc.functions[5].core_no, 6);
  CU_ASSERT_EQUAL(config.proc.functions[6].core_no, 7);
  CU_ASSERT_EQUAL(config.proc.functions[7].core_no, 8);
}

// TEST02：proc_table取得失敗
static void UT_config_load_proc_info_02(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-2_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST03：proc_tableが配列型以外
static void UT_config_load_proc_info_03(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-3_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST04：proc_tableの要素数が必要な情報数より少ない
static void UT_config_load_proc_info_04(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 1, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST05：proc_tableに指定node_idのデータがない ※発生不可
//static void UT_config_load_proc_info_02(void) {
//  int ret = -1;
//  struct spp_config_area config;
//  memset(&config, 0x00, sizeof(struct spp_config_area));
//
//  /* 試験用コンフィグ指定 */
//  strcpy(stub_config_file_name, "spp_config/10-5_vf.json");
//
//  /* Config load */
//  json_error_t json_error;
//  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
//  if (obj != NULL) {
//    /* 試験関数起動 */
//    ret = config_load_proc_info(obj, 0, &config);
//  }
//
//  /* 確認ポイントチェック */
//  CU_ASSERT_EQUAL(ret, -1);
//}

// TEST06：nameデータがない
static void UT_config_load_proc_info_06(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-6_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST07：VHOST数取得失敗
static void UT_config_load_proc_info_07(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-7_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST08：RING数取得失敗
static void UT_config_load_proc_info_08(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-8_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST09：functions取得失敗
static void UT_config_load_proc_info_09(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-9_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST10：functionssが配列型以外
static void UT_config_load_proc_info_10(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-10_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST11：functionsの要素数が0
static void UT_config_load_proc_info_11(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-11_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST12：functionsの要素数が上限越え
static void UT_config_load_proc_info_12(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-12_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST13：core番号取得失敗
static void UT_config_load_proc_info_13(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-13_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST14：処理種別取得失敗
static void UT_config_load_proc_info_14(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-14_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST15：不明な処理種別
static void UT_config_load_proc_info_15(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-15_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST16：受信ポート取得処理失敗
static void UT_config_load_proc_info_16(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-16_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST17：送信ポート取得失敗
static void UT_config_load_proc_info_17(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/10-17_vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret = config_load_proc_info(obj, 0, &config);
  }

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// =============================================================================
// テストケース11 spp_config_load_file
// =============================================================================
// TEST01：正常終了
static void UT_spp_config_load_file_01(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* 試験関数起動 */
  ret = spp_config_load_file(SPP_CONFIG_FILE_PATH, 0, &config);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, 0);
  CU_ASSERT_STRING_EQUAL(config.proc.name, "vf0");
  CU_ASSERT_EQUAL(config.proc.num_vhost, 3);
  CU_ASSERT_EQUAL(config.proc.num_ring, 6);
  CU_ASSERT_EQUAL(config.proc.functions[0].core_no, 1);
  CU_ASSERT_EQUAL(config.proc.functions[1].core_no, 2);
  CU_ASSERT_EQUAL(config.proc.functions[2].core_no, 3);
  CU_ASSERT_EQUAL(config.proc.functions[3].core_no, 4);
  CU_ASSERT_EQUAL(config.proc.functions[4].core_no, 5);
  CU_ASSERT_EQUAL(config.proc.functions[5].core_no, 6);
  CU_ASSERT_EQUAL(config.proc.functions[6].core_no, 7);
  CU_ASSERT_EQUAL(config.proc.functions[7].core_no, 8);
}

// TEST02：コンフィグファイル読み込み失敗
static void UT_spp_config_load_file_02(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf2.json");

  /* 試験関数起動 */
  ret = spp_config_load_file(SPP_CONFIG_FILE_PATH, 0, &config);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST03：classifier_table読み込み失敗
static void UT_spp_config_load_file_03(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/11-3_vf.json");

  /* 試験関数起動 */
  ret = spp_config_load_file(SPP_CONFIG_FILE_PATH, 0, &config);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// TEST04：proc_info読み込み失敗
static void UT_spp_config_load_file_04(void) {
  int ret = -1;
  struct spp_config_area config;
  memset(&config, 0x00, sizeof(struct spp_config_area));

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/11-4_vf.json");

  /* 試験関数起動 */
  ret = spp_config_load_file(SPP_CONFIG_FILE_PATH, 0, &config);

  /* 確認ポイントチェック */
  CU_ASSERT_EQUAL(ret, -1);
}

// =============================================================================
// テストケース12 spp_config_get_path_obj
// =============================================================================
// TEST01：正常終了(配列あり)
static void UT_spp_config_get_path_obj_01(void) {
  json_t *ret_obj = NULL;
  int ret = 0;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$.vfs[0].num_vhost");
    if (ret_obj != NULL) {
      ret = json_integer_value(ret_obj);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NOT_NULL(ret_obj);
  CU_ASSERT_EQUAL(ret, 3);
}

// TEST02：正常終了(配列なし)
static void UT_spp_config_get_path_obj_02(void) {
  json_t *ret_obj = NULL;
  const char *ret_str = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$.classifier_table.name");
    if (ret_obj != NULL) {
      ret_str = json_string_value(ret_obj);
    }
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NOT_NULL(ret_obj);
  CU_ASSERT_STRING_EQUAL(ret_str, "classifier_mac_table");
}

// TEST03：先頭が$以外
static void UT_spp_config_get_path_obj_03(void) {
  json_t *ret_obj = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "classifier_table.name");
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NULL(ret_obj);
}

// TEST04：先頭が$.以外
static void UT_spp_config_get_path_obj_04(void) {
  json_t *ret_obj = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$classifier_table.name");
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NULL(ret_obj);
}

// TEST05：パスの文字数上限越え
static void UT_spp_config_get_path_obj_05(void) {
  json_t *ret_obj = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$.classifier_table.name.01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NULL(ret_obj);
}

// TEST06：存在しないパラメータを指定
static void UT_spp_config_get_path_obj_06(void) {
  json_t *ret_obj = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$.name");
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NULL(ret_obj);
}

// TEST07：配列の要素番号なし
static void UT_spp_config_get_path_obj_07(void) {
  json_t *ret_obj = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$.vfs[].core");
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NULL(ret_obj);
}

// TEST08：配列の閉じ括弧なし
static void UT_spp_config_get_path_obj_08(void) {
  json_t *ret_obj = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$.vfs[8.core");
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NULL(ret_obj);
}

// TEST09：配列の要素番号上限越え
static void UT_spp_config_get_path_obj_09(void) {
  json_t *ret_obj = NULL;

  /* 試験用コンフィグ指定 */
  strcpy(stub_config_file_name, "spp_config/vf.json");

  /* Config load */
  json_error_t json_error;
  json_t *obj = json_load_file(SPP_CONFIG_FILE_PATH, 0, &json_error);
  if (obj != NULL) {
    /* 試験関数起動 */
    ret_obj = spp_config_get_path_obj(obj, "$.vfs[8].core");
  }

  /* 確認ポイントチェック */
  CU_ASSERT_PTR_NULL(ret_obj);
}

// =============================================================================
// Main処理　※．テストケースの呼び出しはここに追加して下さい
// =============================================================================
int main(int argc, char **argv) {
  CU_initialize_registry();
  // ※．テスト対象に応じてCU_add_suiteの引数は書き換えてください
  CU_pSuite suite = CU_add_suite("spp_config_test", setup, teardown);

  /**    ここにテストコードの呼び出しを追加してください      **/
  // Config機能 config_get_int_value
  CU_ADD_TEST(suite, UT_config_get_int_value_01);
  CU_ADD_TEST(suite, UT_config_get_int_value_02);
  CU_ADD_TEST(suite, UT_config_get_int_value_03);

  // Config機能 config_get_str_value
  CU_ADD_TEST(suite, UT_config_get_str_value_01);
  CU_ADD_TEST(suite, UT_config_get_str_value_02);
  CU_ADD_TEST(suite, UT_config_get_str_value_03);

  // Config機能 config_init_data
  CU_ADD_TEST(suite, UT_config_init_data_01);

  // Config機能 spp_config_get_if_info
  CU_ADD_TEST(suite, UT_spp_config_get_if_info_01);
  CU_ADD_TEST(suite, UT_spp_config_get_if_info_02);
  CU_ADD_TEST(suite, UT_spp_config_get_if_info_03);
  CU_ADD_TEST(suite, UT_spp_config_get_if_info_04);
  CU_ADD_TEST(suite, UT_spp_config_get_if_info_05);
  CU_ADD_TEST(suite, UT_spp_config_get_if_info_06);

  // Config機能 spp_config_change_mac_str_to_int64
  CU_ADD_TEST(suite, UT_spp_config_change_mac_str_to_int64_01);
  CU_ADD_TEST(suite, UT_spp_config_change_mac_str_to_int64_02);
  CU_ADD_TEST(suite, UT_spp_config_change_mac_str_to_int64_03);

  // Config機能 config_load_classifier_table
  CU_ADD_TEST(suite, UT_config_load_classifier_table_01);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_02);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_03);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_04);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_05);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_06);
//  CU_ADD_TEST(suite, UT_config_load_classifier_table_07);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_08);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_09);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_10);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_11);
  CU_ADD_TEST(suite, UT_config_load_classifier_table_12);

  // Config機能 config_change_core_type
  CU_ADD_TEST(suite, UT_config_change_core_type_01);
  CU_ADD_TEST(suite, UT_config_change_core_type_02);
  CU_ADD_TEST(suite, UT_config_change_core_type_03);
  CU_ADD_TEST(suite, UT_config_change_core_type_04);

  // Config機能 config_set_rx_port
  CU_ADD_TEST(suite, UT_config_set_rx_port_01);
  CU_ADD_TEST(suite, UT_config_set_rx_port_02);
  CU_ADD_TEST(suite, UT_config_set_rx_port_03);
  CU_ADD_TEST(suite, UT_config_set_rx_port_04);
  CU_ADD_TEST(suite, UT_config_set_rx_port_05);
  CU_ADD_TEST(suite, UT_config_set_rx_port_06);
  CU_ADD_TEST(suite, UT_config_set_rx_port_07);
  CU_ADD_TEST(suite, UT_config_set_rx_port_08);
  CU_ADD_TEST(suite, UT_config_set_rx_port_09);
  CU_ADD_TEST(suite, UT_config_set_rx_port_10);
  CU_ADD_TEST(suite, UT_config_set_rx_port_11);

  // Config機能 config_set_tx_port
  CU_ADD_TEST(suite, UT_config_set_tx_port_01);
  CU_ADD_TEST(suite, UT_config_set_tx_port_02);
  CU_ADD_TEST(suite, UT_config_set_tx_port_03);
  CU_ADD_TEST(suite, UT_config_set_tx_port_04);
  CU_ADD_TEST(suite, UT_config_set_tx_port_05);
  CU_ADD_TEST(suite, UT_config_set_tx_port_06);
  CU_ADD_TEST(suite, UT_config_set_tx_port_07);
  CU_ADD_TEST(suite, UT_config_set_tx_port_08);
  CU_ADD_TEST(suite, UT_config_set_tx_port_09);
  CU_ADD_TEST(suite, UT_config_set_tx_port_10);
  CU_ADD_TEST(suite, UT_config_set_tx_port_11);
  CU_ADD_TEST(suite, UT_config_set_tx_port_12);
  CU_ADD_TEST(suite, UT_config_set_tx_port_13);

  // Config機能 config_load_proc_info
  CU_ADD_TEST(suite, UT_config_load_proc_info_01);
  CU_ADD_TEST(suite, UT_config_load_proc_info_02);
  CU_ADD_TEST(suite, UT_config_load_proc_info_03);
  CU_ADD_TEST(suite, UT_config_load_proc_info_04);
//  CU_ADD_TEST(suite, UT_config_load_proc_info_05);
  CU_ADD_TEST(suite, UT_config_load_proc_info_06);
  CU_ADD_TEST(suite, UT_config_load_proc_info_07);
  CU_ADD_TEST(suite, UT_config_load_proc_info_08);
  CU_ADD_TEST(suite, UT_config_load_proc_info_09);
  CU_ADD_TEST(suite, UT_config_load_proc_info_10);
  CU_ADD_TEST(suite, UT_config_load_proc_info_11);
  CU_ADD_TEST(suite, UT_config_load_proc_info_12);
  CU_ADD_TEST(suite, UT_config_load_proc_info_13);
  CU_ADD_TEST(suite, UT_config_load_proc_info_14);
  CU_ADD_TEST(suite, UT_config_load_proc_info_15);
  CU_ADD_TEST(suite, UT_config_load_proc_info_16);
  CU_ADD_TEST(suite, UT_config_load_proc_info_17);

  // Config機能 spp_config_load_file
  CU_ADD_TEST(suite, UT_spp_config_load_file_01);
  CU_ADD_TEST(suite, UT_spp_config_load_file_02);
  CU_ADD_TEST(suite, UT_spp_config_load_file_03);
  CU_ADD_TEST(suite, UT_spp_config_load_file_04);

  // Config機能 spp_config_get_path_obj
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_01);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_02);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_03);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_04);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_05);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_06);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_07);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_08);
  CU_ADD_TEST(suite, UT_spp_config_get_path_obj_09);

  /**    ここにテストコードの呼び出しを追加してください      **/
  // "CU_BRM_VERBOSE:Test: test_xxxx ... passd"をコンソールに表示
  CU_basic_set_mode(CU_BRM_VERBOSE);
  if (argc == 1) {
    // ※．テスト対象に応じてCU_set_output_filenameの引数は書き換えてください
    CU_set_output_filename("spp_config_test");
    CU_automated_run_tests();
  } else {
    if (strcmp(argv[1], "-b") == 0) { CU_basic_run_tests(); }
    if (strcmp(argv[1], "-c") == 0) { CU_console_run_tests(); }
  }
  const int failed = CU_get_number_of_failures();
  CU_cleanup_registry();
  return -failed;
}
