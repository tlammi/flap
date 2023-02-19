project('flap', 'cpp', default_options: ['cpp_std=c++20'])

fs = import('fs')

add_project_arguments('-Wfatal-errors', '-fno-rtti', language: 'cpp')

cli11 = subproject('cli11')
cli11_dep = cli11.get_variable('CLI11_dep')

magic_enum = subproject('magic_enum')
magic_enum_dep = magic_enum.get_variable('magic_enum_dep')

pub_incdir = include_directories('include')

subdir('lib')
#subdir('bin')
