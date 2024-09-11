obj-m += ko_n132.o

KDIR =~/KZone/kernel/kernel-v6.6
# KDIR =../../kernel/kernel-v6.4.3/
# KDIR =../../kernel/kernel-v6.10.4/
# KDIR =../../kernel/kernel-v5.10.127/
# KDIR =../../kernel/linux-6.10/

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules -w
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order
