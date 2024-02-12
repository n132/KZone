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






[1]: https://github.com/sefcom/RetSpill
[2]: https://github.com/sefcom/KHeaps
[3]: ./scripts/create-image.sh