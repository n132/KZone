obj-m += ko_n132.o

# KDIR =../../kernel/kernel-v5.18/
# KDIR =../../kernel/kernel-v6.4.3/
# KDIR =../../kernel/kernel-v6.10.4/
KDIR =../../kernel/kernel-v5.10.127/
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules -w
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order
