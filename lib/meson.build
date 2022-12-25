
SRCS = []
DEPS = []

lib_incdir = include_directories('.')

subdir('util')

SRCS += files('consumer.cpp', 'lex.cpp')

libflap = static_library('flap', SRCS, include_directories: [lib_incdir, pub_incdir])

subdir('test')
