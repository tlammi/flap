
SRCS = []
DEPS = []

lib_incdir = include_directories('.')

subdir('util')
subdir('ast')
subdir('consumer')

SRCS += files('consumer.cpp', 'lex.cpp', 'parse.cpp')

libflap = static_library('flap', SRCS,
    include_directories: [lib_incdir, pub_incdir],
    dependencies: DEPS)

subdir('test')
