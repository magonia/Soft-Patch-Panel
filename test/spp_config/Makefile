include ./mk/env.mk

.PHONY: clean

postinstall:
#	@cp -f ../../../../dpdk/mk/defconfig_spp $(DPDK_HOME)/config/

install_dpdk: postinstall
	@cd $(DPDK_HOME); \
	make install T=$(RTE_TARGET);

clean_dpdk:
	@cd ../../../common/;  \
	make clean
	@cd $(DPDK_HOME); \
	make clean T=$(RTE_TARGET);

all:
	@$(MAKE) -f "./mk/build_spp_config.mk"

clean:
	@$(MAKE) -f "./mk/build_spp_config.mk" "clean"

# spp_config
spp_config_test:
	@$(MAKE) -f "./mk/build_spp_config.mk"
spp_config_clean:
	@$(MAKE) -f "./mk/build_spp_config.mk" "clean"
