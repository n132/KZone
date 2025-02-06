# KZone

A Play Ground for Learning Kernel. The infrastructure to play with the Linux kernel.

You can write and compile your kernel module to debug some features you are interested at with this repository.


I steal the scripts from [RetSpill][1] and [KHeap][2]



# How to use this repo

Create an Image

```bash
cd scripts && ./create-image.sh && popd
```

Compile the Linux Kernel

```bash
cd kernel && ./build.sh v5.4.268
cp ./kernel-v5.4.268/arch/x86/boot/bzImage ../zone
popd
```


Run the kernel in a VM

```bash
cd zone
./kz
```

Compile your kernel modules

```bash
cd zone/module/
make
popd
```

Play with your modules

```bash
cd zone
./kz cp ./module/ko_n132.ko
```

# Create an Image

Use the [script][3] to create an image. 

```bash
# you may need
# sudo apt install debootstrap
./create-image.sh --distribution bookworm
```

You can `mount` and `umount` to modify the image:

```bash
sudo mount ./bookworm.img /mnt/
# Modify the content of the image
sudo umount  /mnt/
```

# Compile Linux Kernel


Use this [script][4] to compile the kernel.

Example, `./build.sh v5.4.268`.

Sometimes (v5.4.268 is fine) you need to patch the default config for some new versions or compile the modules: You may need to compile the modules and copy them to the disk imge, which may also require you to expand your disk image to store these compiled modules: aka modify the script and recreate the disk. Kindly attach the commands you may need if you really want to use the oldconfig:

```bash
make CC=clang -j$(nproc) modules_install INSTALL_MOD_PATH=$where_you_mount_the_disk_img
```

# Script kz

`kz` support 3 sub-command:
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

## vmlinux

- Using `gdb vmlinux` to debug the kernel makes life easier
- If you compile the kernel with keeping debug symbols, you'll find vmlinux at the root of source directory


## extract-vmlinux

- [extract-vmlinux][5] is a tool that extract vmlinux from bzImage.
- Usgae: `extract-vmlinux ./bzImage > vmlinux.raw`

## vmlinux-to-elf

- A [tool][6] to recover symbols from `kallsyms`
- Installation: `pip3 install --upgrade git+https://github.com/marin-m/vmlinux-to-elf`
- Usage: `vmlinux-to-elf ./vmlinux.raw vmlinux`

## Template of x.sh
Format: .img
```bash
#!/bin/sh
gcc ./fs/exp.c -masm=intel -o ./fs/exp -lx -lpthread --static -w &&\
echo "[+] Compile - Done" &&\
cd /home/n132/tap/KZone/scripts
sudo mount buster.img fs
sleep .5
cp /home/n132/tap/KZone/zone/fs/exp /home/n132/tap/KZone/scripts/fs
sudo umount fs
cd /home/n132/tap/KZone/zone/
echo "[+] repacking - Done" &&\
echo "[+] Filesystem - Done" &&\
echo "[...] run.sh" &&\
sudo ./kz run
```


# TODO
- support lower versions of kernel

[1]: https://github.com/sefcom/RetSpill
[2]: https://github.com/sefcom/KHeaps
[3]: ./scripts/create-image.sh
[4]: ./kernel/build.sh
[5]: https://github.com/torvalds/linux/blob/master/scripts/extract-vmlinux
[6]: https://github.com/marin-m/vmlinux-to-elf
