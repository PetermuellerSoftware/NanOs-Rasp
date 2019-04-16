#!/bin/bash

export TARGET=$(./target.sh)

export CC="$HOME/opt/cross/bin/${TARGET}-gcc"
export OBJCOPY="$HOME/opt/cross/bin/${TARGET}-objcopy"

make
