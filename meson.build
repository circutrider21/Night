# Copyright (c) 2021 Night Developers. All Rights Reserved
project('Night', 'c', version: '0.3.1')

# TODO: Add Configuration Support
# conf_data = configuration_data()
# conf_data.set('version', meson.project_version())
# configure_file(input: 'include/Sigma/config.h.in', output: 'config.h', configuration: conf_data)

cflags = ['-fno-PIC', '-fstrength-reduce', '-fomit-frame-pointer', 
          '-fno-builtin', '-nostdlib', '-ffreestanding', '-std=c99']

link_file = meson.source_root() + '/arch/' + get_option('arch') + '/link.ld'
link_am = ['-Wl,-T', '-Wl,' + link_file, '-nostdlib',  
    '-fno-PIC', '-no-pie', '-Wl,--build-id=none']
clang_target = ''

kernel_src = files(
  'kernel/src/kernel/kernel.c',
  'kernel/src/kernel/logger.c',
  'kernel/src/drivers/display/legcon.c',
  'kernel/src/drivers/display/vbe.c'
)

kernel_inc = include_directories('kernel/include', 'lib/include', 'arch/' + get_option('arch') + '/include')

if get_option('arch') == 'x86-64'
  cflags += ['-m64', '-march=x86-64', '-mcmodel=kernel']
  clang_target = 'x86_64-unknown-none-elf'
  link_am += ['-mcmodel=kernel', '-Wl,-z,max-page-size=0x1000,-n']
elif get_option('arch') == 'x86-32'
  cflags += ['-m32', '-march=i386']
  clang_target = 'i386-unknown-none-elf'
  link_am += ['-Wl,-melf_i386']
endif

# Clang support cross-compiling by default
# No cross-compiler required

if meson.get_compiler('c').get_id() == 'clang'
  cflags += ['--target=' + clang_target]
endif

subdir('arch/' + get_option('arch') + '/')
subdir('lib/libk')

deps = [libk, libarch]

executable('krnl', kernel_src, link_with: deps, include_directories: kernel_inc, link_depends: link_file, c_args: cflags, link_args: link_am)
