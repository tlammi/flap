
deps = [libflap_dep, libflap_consumer_llvm_dep, libflap_consumer_debug_dep, cli11_dep]

executable('flap', 'flap.cpp',
    include_directories: pub_incdir,
    dependencies: deps)

fs.copyfile('flapi', 'flapi')
