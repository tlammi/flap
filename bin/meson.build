
deps = [libflap_dep, libflap_consumer_llvm_dep, cli11_dep]

executable('flapc', ['flapc.cpp', 'cli.cpp'],
    include_directories: pub_incdir,
    dependencies: deps)

fs.copyfile('flapi', 'flapi')
