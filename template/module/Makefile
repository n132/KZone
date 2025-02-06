obj-m += ko_n132.o

KDIR =/home/n132/KZone/kernel/kernel-v6.6.62

all:
	$(MAKE) KCFLAGS="-Wno-error" -C $(KDIR) M=$(PWD) modules -w
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *.mod ./.*.cmd
