C = gcc
DPDK_HOME = /home/operad/work/dpdk-17.05
RTE_TARGET = x86_64-native-linuxapp-gcc
RTE_INCLUDE = $(DPDK_HOME)/$(RTE_TARGET)/include
RTE_LIB = $(DPDK_HOME)/$(RTE_TARGET)/lib
DEFAULT_CFLAGS = -Wall -std=gnu99 -include $(RTE_INCLUDE)/rte_config.h \
	-I/usr/local/include \
	-I ../../src/common/include/
DEFAULT_LDFLAGS = -L/usr/lib -L/usr/local/lib -L$(RTE_LIB)
DEFAULT_LDLIBS = -Wl,--export-dynamic -Wl,--whole-archive -ldpdk -Wl,--no-whole-archive -ljansson -lbsd -lpthread -ldl -lm
DPDK_CONFIG_NAME = defconfig_$(RTE_TARGET)
