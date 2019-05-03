
ARCH?=${TARGET}



EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

ARCHDIR=arch/$(ARCH)
BUILDDIR?=build

CFLAGS += -g -O2 --sysroot=$(SYSROOT) -pipe
CFLAGS += -I$$SYSROOT/usr/include
CFLAGS += -I$$SYSROOT/usr/include/kernel
#Wanrings
CFLAGS += -Wall -Wextra 

KCFLAGS += -fpic -ffreestanding -Wall -Wextra 

ASMFLAGS += -Wall -Wextra 
ASMFLAGS += -fpic -ffreestanding -c


KCPPFLAGS += -D__is_kernel
KCPPFLAGS += -D__log_uart
KCPPFLAGS += -D__qemu

KLDFLAGS += 

LIBS += -nostdlib -lgcc

-include $(ARCHDIR)/Makefile.config

KERNEL_OBJS= \
$(BUILDDIR)/src/kernel.o \
$(BUILDDIR)/printf/printf.o \
$(BUILDDIR)/printf/putchar.o \
$(BUILDDIR)/libk/abort.o \
$(BUILDDIR)/libk/size2str.o \
$(KERNEL_ARCH_OBJS)


OBJS=\
$(BUILDDIR)/$(ARCHDIR)/crti.o \
$(BUILDDIR)/$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(BUILDDIR)/$(ARCHDIR)/crtend.o \
$(BUILDDIR)/$(ARCHDIR)/crtn.o \


LINK_LIST=\
$(LDFLAGS) \
$(BUILDDIR)/$(ARCHDIR)/crti.o \
$(BUILDDIR)/$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(BUILDDIR)/$(ARCHDIR)/crtend.o \
$(BUILDDIR)/$(ARCHDIR)/crtn.o \

.phony: all prepare-dir


all: prepare-dir $(BUILDDIR)/kernel8.img

$(BUILDDIR)/kernel8.img: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld  -o $(BUILDDIR)/nanos.elf $(CFLAGS) $(KCFLAGS) $(LINK_LIST)
	$(OBJCOPY) $(BUILDDIR)/nanos.elf -O binary $(BUILDDIR)/kernel8.img
	
$(BUILDDIR)/$(ARCHDIR)/crtbegin.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
$(BUILDDIR)/$(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
$(BUILDDIR)/$(ARCHDIR)/crti.o: 
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
$(BUILDDIR)/$(ARCHDIR)/crtn.o: 
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
 
$(BUILDDIR)/%.o: %.S
	$(CC) -MD -c $< -o $@ $(ASMFLAGS) $(ASMCFLAGS) 

$(BUILDDIR)/%.o: %.c
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(KCFLAGS) $(KCPPFLAGS) $(CPPFLAGS)

prepare-dir:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/libk
	mkdir -p $(BUILDDIR)/src
	mkdir -p $(BUILDDIR)/printf
	mkdir -p $(BUILDDIR)/$(ARCHDIR)

clean:
	rm -rf $(BUILDDIR)

-include $(BUILDDIR)/*.d
-include $(BUILDDIR)/$(ARCHDIR)/*.d
