#!/bin/sh

# Builds an ISO for the 32-bit version of the night kernel

# NOTE: Only works when called from root of src dir and with build dir "buildx32"

# REQUIREMENTS:
#   grub-mkrescue
#   Sudo Permission

# Make ISO root and copy files

mkdir -p iso-root/boot/grub

cp buildx32/krnl iso-root/boot/krnl
cp extra/grub.cfg iso-root/boot/grub/grub.cfg

# Install grub and make ISO

grub-mkrescue -o Night-x86_32.iso iso-root
