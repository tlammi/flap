
SRCS = []
DEPS = []

lib_incdir = include_directories('.')

subdir('util')
subdir('ast')

SRCS += files('lex.cpp', 'parse.cpp')

libflap = static_library('flap', SRCS,
    include_directories: [lib_incdir, pub_incdir],
    dependencies: DEPS)

libflap_dep = declare_dependency(link_with: libflap)

subdir('test')
