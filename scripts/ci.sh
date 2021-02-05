#!/bin/sh

# Install dependencies first
echo Installing Dependencies...
apt update
apt install ninja-build unzip
wget https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest
unzip latest
rm -rf .cipdpkg latest
mv gn /usr/bin


# Run 32-bit build first
mkdir build32
cp build/preset/x86_32.gn build32/args.gn
gn gen build32
ninja -C build32

# Then 64-bit build
mkdir build64
cp build/preset/x86_64.gn build64/args.gn
gn gen build64
ninja -C build64

echo Complete!
