#! /bin/bash

file=${1%as}abc;
avmplus=nodeas/platform/mac/avmshell/build/Debug/shell
java -jar asc.jar -import nodeas/core/builtin.abc -import nodeas/shell/shell_toplevel.abc $1
$avmplus $file
rm $file
