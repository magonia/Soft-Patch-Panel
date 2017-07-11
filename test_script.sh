#!/bin/bash
cmd="env | grep -i rte"
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
