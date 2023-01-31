
gtest_deps = [dependency('gtest'), dependency('gtest_main')]

test_util = executable('test_util', files('test.cpp'), dependencies: DEPS + gtest_deps, include_directories: lib_incdir)

test('Util', test_util)

