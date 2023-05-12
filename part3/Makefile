obj-y := syscall.o
obj-m += elevator.o

PWD := $(shell pwd)
KDIR := /lib/modules/`uname -r`/build

all:
	$(MAKE) -C $(KDIR) SUBDIR=$(PWD) modules

clean:
	clear; rm -f *.o *.ko *.mod.* Module.* modules.*
