#!/bin/bash
cmd="source ~/.bashrc"
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
