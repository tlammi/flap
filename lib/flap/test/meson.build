
test_kwargs = {
  'dependencies': [dependency('gtest'), dependency('gtest_main')],
  'link_with': libflap,
  'include_directories': [lib_incdir, pub_incdir]
}

test_lex = executable('test_lex', 'lex.cpp', kwargs: test_kwargs)

test('Lexer', test_lex)
