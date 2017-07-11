#!/bin/bash
cmd="export RTE_SDK=/home/gitlab-runner/dpdk-17.05"
echo "> $cmd"
$cmd

cmd="export RTE_TARGET=x86_64-native-linuxapp-gcc"
echo "> $cmd"
$cmd

cmd="source /home/gitlab-runner/.bashrc"
echo "> $cmd"
$cmd

cmd="$RTE_SDK"
echo "> $cmd"
$cmd

cmd="pwd"
echo "> $cmd"
$cmd

cmd="cd src"
echo "> $cmd"
$cmd

cmd="make"
echo "> $cmd"
$cmd
exit $?
