







# TODO: get universal arch directory

export SYSROOT=$(PWD)/sysroot/



.phony: sysroot include clean



all: kernel


kernel: include
	cd ../kernel && $(MAKE) 

sysroot:
	mkdir -p sysroot
	
include: sysroot
	mkdir -p sysroot/usr/include/kernel/arch
	
	@cp -u -r ../kernel/include/* sysroot/usr/include/kernel
	@echo "Copy kernel/include to sysroot"
	@rm -rf sysroot/usr/include/kernel/arch/*
	@cp -u -r ../kernel/include/arch/${TARGET}/* sysroot/usr/include/kernel/arch
	@echo "Copy kernel/include/arch to sysroot"


clean:
	rm -rf sysroot
	cd ../kernel && $(MAKE) clean

	