#!/bin/bash
cmd="echo \$RTE_SDK"
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
