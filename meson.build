project('flap', 'cpp', default_options: ['cpp_std=c++20'])

add_project_arguments('-Wfatal-errors', '-fno-rtti', language: 'cpp')

cli11 = subproject('cli11')
cli11_dep = cli11.get_variable('CLI11_dep')

pub_incdir = include_directories('include')

subdir('consumer')
subdir('lib')
subdir('bin')
