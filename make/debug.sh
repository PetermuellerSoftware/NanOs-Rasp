#!/bin/bash


echo "starting qemu in screen seesion NanOs" 
screen -dmS NanOs ./qemu-rasp.sh -s -S

sleep 1s

echo "Starting Debugger GDB"
aarch64-elf-gdb ../kernel/build/nanos.elf #-target "remote localhost:1234"

