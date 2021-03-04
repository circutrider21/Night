libk_src = files(
  'src/memory.c',
  'src/string.c'
)

libk_inc = include_directories('../../kernel/include', '../../lib/include', '../../arch/' + get_option('arch') + '/include')

libk = static_library('libk', libk_src, include_directories: libk_inc, c_args: cflags)
