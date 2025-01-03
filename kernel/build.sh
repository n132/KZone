#!/bin/bash
set -x
echo "Downloading the source code of" $1
rm -rf kernel-$1
git clone --branch $1 --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git kernel-$1
WorkDIR=`realpath ./kernel-$1`
docker run -v$WorkDIR:$WorkDIR n132/kernel-compiler:20.04 bash -c "cd $WorkDIR && make olddefconfig && sed -i 's/CONFIG_DEBUG_INFO_NONE=y/CONFIG_DEBUG_INFO=y/' ./.config && echo -e 'CONFIG_DEBUG_INFO=y\nCONFIG_DEBUG_INFO_DWARF4=y' >> ./.config  && make -j`nproc`"
