#!/bin/sh

# Builds an VHD for the 64-bit version of the Night kernel

# NOTE: Only works when called from root of src dir and with build dir "buildx64"

# REQUIREMENTS:
#   Sudo Permission

# Get and Build Limine

git clone --branch v1.0-branch https://github.com/limine-bootloader/limine.git
cd limine && make && cd ..

# Get and build echfs

git clone --depth 1 https://github.com/echfs/echfs.git
cd echfs && make install-utils && cd ..

# Build the image

dd if=/dev/zero bs=1M count=0 seek=5 of=Night-x86_64.vhd
parted -s Night-x86_64.vhd mklabel msdos
parted -s Night-x86_64.vhd mkpart primary 1 100%
parted -s Night-x86_64.vhd set 1 boot on # Workaround for buggy BIOSes

echfs-utils -m -p0 Night-x86_64.vhd quick-format 32768
echfs-utils -m -p0 Night-x86_64.vhd import extra/limine.cfg limine.cfg
echfs-utils -m -p0 Night-x86_64.vhd import buildx64/krnl krnl

./limine/limine-install Night-x86_64.vhd
