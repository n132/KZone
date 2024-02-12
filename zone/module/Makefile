obj-m += ko_n132.o

KDIR =../../kernel/kernel-v5.4.268/
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order