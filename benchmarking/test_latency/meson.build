project('benchmarks', 'cpp',    # Project name and language
    default_options : ['cpp_std=c++17']  # Correct options syntax
)

# Dependenciess
boost = dependency('boost', modules: ['system'
])
json_dep = dependency('nlohmann_json', required: true)
ssl = dependency('openssl')

# Sources
src_files = [
    'main.cpp',
    'User.cpp',
    'Api.cpp',
    'Websockets/Socket.cpp',
    'Websockets/boost.cpp',
    'Websockets/zsocket.cpp'
]



# Executable target
executable('bench', src_files, dependencies: [boost, ssl])