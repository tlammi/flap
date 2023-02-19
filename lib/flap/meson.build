
LIBFLAP_SRCS = ['parse.cpp', 'lex.cpp']

libflap_incdirs = [pub_incdir, lib_incdir]

magic_enum = subproject('magic_enum')
magic_enum_dep = magic_enum.get_variable('magic_enum_dep')
libflap = library('flap', LIBFLAP_SRCS, include_directories: libflap_incdirs, dependencies: [magic_enum_dep])



subdir('test')
