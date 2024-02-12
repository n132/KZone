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

TODO

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


# TODO
- [ ] Solve the networking problem
- [ ] Merge Kernel Compilation part into this repo
- [ ] Solving cp and connect issues 


[1]: https://github.com/sefcom/RetSpill
[2]: https://github.com/sefcom/KHeaps
[3]: ./scripts/create-image.sh