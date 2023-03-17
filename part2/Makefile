obj-m += my_timer.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules; insmod my_timer.ko;

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
