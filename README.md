# KZone

KZone is a playground for learning and experimenting with the Linux kernel. This infrastructure allows you to write, compile, and debug kernel modules with ease.

Parts of the scripts were adapted from RetSpill and KHeap.


# Getting Started

```sh
git clone https://github.com/n132/KZone.git
cd KZone
```

## Create an Image

Use the [script][3] to create an image. 

```bash
# you may need
# sudo apt install debootstrap
./create-image.sh --distribution bookworm
```

## Create the zone
```bash
kz zone zone_v6.13 v6.13
cd zone_v6.13
kz run
```

# Using kz

The kz command provides several sub-commands to manage the virtual machine.

# Commands
- kz (or kz run):
Starts a VM using the first disk image ($(pwd)/img/*.img) and the first kernel image ($(pwd)/bzImage).

- kz cp <host_file>:
Copies a file from the host machine to the VM.

- kz sh:
Connects to the VM shell using SSH.

- kz zone <name_of_zone> <kernel_version>:
Create a zone for a specific kernel

- kz switch <fs_name>:
Switches the VM filesystem to a backup stored in a fs_<name> directory under scripts.




[1]: https://github.com/sefcom/RetSpill
[2]: https://github.com/sefcom/KHeaps
[3]: ./scripts/create-image.sh
[4]: ./kernel/build.sh
[5]: https://github.com/torvalds/linux/blob/master/scripts/extract-vmlinux
[6]: https://github.com/marin-m/vmlinux-to-elf



# More

## Modify Image (Optional)
You can `mount` and `umount` to modify the image:

```bash
sudo mount ./bookworm.img /mnt/
# Modify the content of the image
sudo umount  /mnt/
```


## Compile Kernel (optional)

Use this [script][4] to compile the kernel.

Example, `./build.sh v6.6.66`.

```bash
cd kernel && ./build.sh v6.6.66
cp ./kernel-v6.6.66/arch/x86/boot/bzImage ../zone
cp ./kernel-v6.6.66/vmlinux ../zone
popd
```

Sometimes (v6.6.66 is fine) you need to patch the default config for some new versions or compile the modules: You may need to compile the modules and copy them to the disk imge, which may also require you to expand your disk image to store these compiled modules: aka modify the script and recreate the disk. Kindly attach the commands you may need if you really want to use the oldconfig:

```bash
make CC=clang -j$(nproc) modules_install INSTALL_MOD_PATH=$where_you_mount_the_disk_img
```


## Compile Kernel Modules (optional)

```bash
cd <your_zone>/module/
make
```
