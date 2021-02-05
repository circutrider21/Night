#!/bin/sh

# Install dependencies first
echo Installing Dependencies...
apt update
apt install nasm
wget https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest
unzip latest
rm -rf .cipdpkg latest
mv gn /usr/bin
wget https://github.com/ninja-build/ninja/releases/download/v1.10.2/ninja-linux.zip
unzip *.zip
mv ninja /usr/bin
rm -rf *.zip


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
