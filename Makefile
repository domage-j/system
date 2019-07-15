##
## Makefile - top level makefile
## System sources under license MIT
##

VERSION		=	v0.0.1
KERNEL		=	system
KERNEL_IMG	=	vmsystem.img
KERNEL_SYM	=	kernel.elf

ARCH	=	x86
TARGET	=	arch/$(ARCH)

all:
	$(MAKE) -C $(TARGET) all

clean:
	$(MAKE) -C $(TARGET) clean

run:
	$(MAKE) -C $(TARGET) run

debug:
	$(MAKE) -C $(TARGET) debug

re:	
	$(MAKE) -C $(TARGET) re

.PHONY:	all clean re run debug

