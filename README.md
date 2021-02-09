# Night

### What is this???

The Night Kernel is a simple monolithic multi-arch kernel. It is a hobby project of mine.

Some things that I currrently have done...

- [x] Basic layout and build system
- [x] Print "Hello, World!" to the screen
- [x] Setup both x32 and x64 gdt
- [ ] 32 and 64-bit IDT
- [ ] APIC and PIC Support
- [ ] Memory manager
- [ ] And many other things

Like I said this kernel is in its very, very early stages.
It is also chaniging rapidly so be tuned for more changes.

### Building

Prebuilt distributions of both the 32-bit kernel and the 64-bit kernel are availible in the releases tab.
They look like this...

1. Night-x64.zip - A zipfile with the kernel and an EFI Bootloader
2. Night-x32.iso - An ISO that contains GRUB and the Kernel Itself
3. Night-duo.iso - An ISO with both the 32 and 64-bit versions of the kernel alongside GRUB

For more information on how to boot these various distros, See [Docs](docs/RUNNING.md)

As for building, See [BUILDING](docs/BUILDING.md)

### Contributing

If you want to contribute to the kernel, You are absolutly welclome.
Just be sure to follow the [Guidelines](docs/STANDARD.md)
If you want to help, just let me know in the discussions tab

### Issues

If you have any problem of any kind, first check the documentation.
If that dosen't do it, then open an issue.

**Copyright (c) 2021 The Developers of the Night Kernel**
