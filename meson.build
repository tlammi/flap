project('flap', 'cpp', default_options: ['cpp_std=c++20'])

fs = import('fs')

add_project_arguments('-Wfatal-errors', '-fno-rtti', language: 'cpp')

cli11 = subproject('cli11')
cli11_dep = cli11.get_variable('CLI11_dep')


pub_incdir = include_directories('include')
priv_incdir = include_directories('lib')

SRCS = []

subdir('lib')

tests = []
srcs = []

foreach src : SRCS
  stem = fs.stem(src)
  if stem.startswith('test_')
    tests += src
  else
    srcs += src
  endif
endforeach

libflap = library('flap', srcs, include_directories: [pub_incdir, priv_incdir])

libflap_dep = declare_dependency(link_with: libflap)
test_args = {
  'include_directories': [pub_incdir, priv_incdir],
  'dependencies': [
    dependency('gtest'),
    dependency('gmock'),
    dependency('gtest_main'),
    libflap_dep
  ]
}

foreach src : tests
  stem = fs.stem(src)
  test_exe = executable(stem, src, kwargs: test_args)
  name = stem.replace('_', ' ')
  test(name, test_exe)
endforeach
