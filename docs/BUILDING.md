<h1 align="center"> Build Instructions for Night Kernel </h1>

<div align="center">

**Note: The kernel can't be built on windows, so I reccomend you get [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10)**

</div>

## Using GN

GN is a Powerful and Open-Source build system used in many projects, such as [Fuchisa](fuchsia.dev) and [Google Chrome](google.com/chrome)

GN also uses Ninja as a backend but can also generate IDE project files (like Visual Studio and XCode).

Finnally, GN happens to be the build system of the Night Kernel (Personal Prefrence).

Anyways, on to installation.


### Installing Ninja

To install Ninja, there are two ways.

Method 1

```` bash
$ sudo apt-get install ninja-build
````

Method 2

```` bash
$ pip install ninja
````

*Note: Only use the second method if you don't have administrator permissions*

### Installing GN

Sadly, GN is not availible as a package and you will have to install it manually from the links below

- [Linux](https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest)
- [Mac OS](https://chrome-infra-packages.appspot.com/dl/gn/gn/mac-amd64/+/latest)

Once downloaded, unzip the file and move the GN binary into your /usr/bin directory

Now, we are ready to build!

## Building the kernel itself

First, make a build directory in the root dir (If you want to make an ISO, it has to be named out)

Then copy the configuration file from build/preset/ to out/args.gn

The configuration files have diffrent names for diffrent purposes, a brief explanation is below...

1. x86_32.gn - Use this for the x86-32 arch
2. x86_64.gn - Use this for the x86-64 arch
3. x86_64-clang.gn - Same as above, but with clang

Feel free to look and modify the configs, just don't mess with the arch flags

Your structure should now look like this...

    <Root Dir> \
               | -- Other folders
               | -- out \
                        | -- args.gn - The Confugration file you copyied.
                        
  
Now, building the kernel is as simple as running the following commands

````bash
gn gen out
ninja -C out
````
The compiled kernel is in out/krnl

### Making an ISO (Or Image)

If you compiled for the x86-32 Arch, then run the following
````bash
./scripts/make-iso.sh
````
The ISO should be in out/boot.iso

If you compiled for the x86-64 Arch, then run the following
````bash
./scripts/make-efi.sh
````
The image should be in out/boot.zip

To boot these images/files, see (Here)[RUNNING.md]

**Copyright (c) 2021 The Developers of the Night Kernel**
