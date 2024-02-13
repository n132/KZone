# KZone

A Play Ground for Learning Kernel. The infrastructure to play with the Linux kernel.

You can write and compile your kernel module to debug some features you are interested at with this repository.


I steal the scripts from [RetSpill][1] and [KHeap][2]



# How to use this repo

1. Create an Image

```bash
cd scripts && ./create-image.sh && popd
```

2. Compile the Linux Kernel

```bash
cd kernel && ./build.sh v5.4.268
cp ./kernel-v5.4.268/arch/x86/boot/bzImage ../zone
popd
```


3. Run the kernel in a VM

```bash
cd zone
./kz
```

4. Compile your kernel modules

```bash
cd zone/module/
make
popd
```

5. Play with your modules

```bash
cd zone
./kz cp ./module/ko_n132.ko
```

# Create Image

Use the [script][3] to create an image. 

```bash
./create-image.sh --distribution bookworm
```

You can `mount` and `umount` to modify the image:

```bash
mount ./bookworm.img /mnt/
# Modify the content of the image
umount  /mnt/
```

# Compile Linux Kernel


Use this [script][4] to compile the kernel.

Example, `./build.sh v5.4.268`.

Sometimes (v5.4.268 is fine) you need to patch the default config for some new versions or compile the modules: You may need to compile the modules and copy them to the disk imge, which may also require you to expand your disk image to store these compiled modules: aka modify the script and recreate the disk. Kindly attach the commands you may need if you really want to use the oldconfig:

```bash
make CC=clang -j$(nproc) modules_install INSTALL_MOD_PATH=$where_you_mount_the_disk_img
```

# kz

kz support 3 sub-command:
- `kz` 
    - Same as `kz run`
- `kz run`
    - Start a VM 
    - Using the fist disk image at `$(pwd)/img/*.img`
    - Using the first Kernel Image at `$(pwd)/bzImage`
- `kz cp <host_file>`
    - Copy the file on host to the VM
- `kz sh`
    - SSH connect to the VM


# Tips for Kernel Debugging

## extract-vmlinux

- [extract-vmlinux][5] is a tool that extract vmlinux from bzImage.
- Usgae: `extract-vmlinux ./bzImage > vmlinux.raw`

## vmlinux-to-elf


- A [tool][6] to recover symbols from `kallsyms`
- Installation: `pip3 install --upgrade git+https://github.com/marin-m/vmlinux-to-elf`
- Usage: `vmlinux-to-elf ./vmlinux.raw vmlinux`



[1]: https://github.com/sefcom/RetSpill
[2]: https://github.com/sefcom/KHeaps
[3]: ./scripts/create-image.sh
[4]: ./kernel/build.sh
[5]: https://github.com/torvalds/linux/blob/master/scripts/extract-vmlinux
[6]: https://github.com/marin-m/vmlinux-to-elf