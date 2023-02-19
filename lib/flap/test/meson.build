
test_kwargs = {
  'dependencies': [dependency('gtest'), dependency('gtest_main')],
  'link_with': libflap,
  'include_directories': libflap_incdirs
}

test_lex = executable('test_lex', 'lex.cpp', kwargs: test_kwargs)

test('Lexer', test_lex)
