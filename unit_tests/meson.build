project('spdlog_test', 'cpp',
    version : '0.1.0',
    default_options : ['cpp_std=c++17'])

# Dependencies
spdlog_dep = dependency('spdlog', required: true)

# Executable target
executable('hello_log',
    'spdlog.cpp',
    dependencies : spdlog_dep
)
