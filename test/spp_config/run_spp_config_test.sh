#!/bin/sh
TARGET_NAME=spp_config

make ${TARGET_NAME}_test clean
make ${TARGET_NAME}_test
#./${TARGET_NAME}_test -b
./${TARGET_NAME}_test
mkdir -p ${TARGET_NAME}/coverage
lcov -c -d ./ -b ./ -o ./${TARGET_NAME}.info
genhtml -o ./${TARGET_NAME}/coverage ./${TARGET_NAME}.info
