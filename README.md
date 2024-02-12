# KZone
A Play Ground for Learning Kernel. The infrastructure to play with the Linux kernel.

You can write and compile your kernel module to debug some features you are interested at with this repository.


I steal the scripts from [RetSpill][1] and [KHeap][2]


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


Knowledge Base: https://n132.github.io/2023/09/29/Kernel-Pwn-Env.html

If it's possible. Try not to use your host's config. If you use your host's config (for example, Ubuntu) to compile the kernel, you may need to compile the modules and copy them to the disk imge, which may also require you to expand your disk image to store these compiled modules: aka modify the script and recreate the disk. Kindly attach the commands you may need if you really want to use the oldconfig:

```bash
make CC=clang -j$(nproc) modules_install INSTALL_MOD_PATH=$where_you_mount_the_disk_img
```

# kz

- Usage: `kz [command]`
- The default command of running kz is `kz run`

## run

Start an VM using 

- Usage: `kz run`
- The fist disk image at `$(pwd)/img/*.img`
- Kernel Image at `$(pwd)/bzImage`


## cp

- Usage: `kz cp <host_file>`
- Copy the file on host to the VM


## sh

- Usage: `kz sh`
- SSH connect to the VM




[1]: https://github.com/sefcom/RetSpill
[2]: https://github.com/sefcom/KHeaps
[3]: ./scripts/create-image.sh