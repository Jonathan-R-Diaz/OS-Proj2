obj-m += elevator.o

all:
	make clean; make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules; insmod elevator.ko; cat /proc/elevator

clean:
	rmmod elevator; make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean; rm .*~
