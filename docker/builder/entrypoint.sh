#!/bin/sh
/usr/local/bin/useridinit
export USER=$(id -un)
export HOME=$(eval echo ~$USER)
"$@"
