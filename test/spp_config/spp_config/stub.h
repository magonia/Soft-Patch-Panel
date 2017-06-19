#pragma once

#include "spp_config.h"

#undef SPP_CONFIG_FILE_PATH
extern char stub_config_file_name[256];
#define SPP_CONFIG_FILE_PATH stub_config_file_name
