#!/bin/bash

./build.sh
#./iso.sh

TARGET=$(./target.sh)

qemu-system-aarch64 $1 -m 256 -M raspi3 -kernel ../kernel/build/kernel8.img -serial null -serial stdio 