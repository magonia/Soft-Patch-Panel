#!/bin/bash
execute(){
echo "> $1"
$1
return $?
}

execute "export RTE_SDK=/home/gitlab-runner/dpdk-17.05"
execute "export RTE_TARGET=x86_64-native-linuxapp-gcc"
execute "source /home/gitlab-runner/.bashrc"
execute "pwd"
execute "cd src"
execute "make"
exit $?
