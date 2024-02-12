echo "Downloading the source code of" $1
rm -rf kernel-$1
git clone --branch $1 --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git kernel-$1
docker run -v`realpath ./kernel-$1`:/mnt  n132/kernel-compiler:20.04 bash -c "cd /mnt && make defconfig && make -j128"
