project('hello', 'cpp',    # Project name and language
    default_options : ['cpp_std=c++17']  # Correct options syntax
)

# Dependenciess
boost = dependency('boost', modules: ['system'
])
spdlog_dep = dependency('spdlog', required: true)
json_dep = dependency('nlohmann_json', required: true)
ssl = dependency('openssl')

# Sources
src_files = [
    'main.cpp',
    'User.cpp',
    'Api.cpp',
    'Websockets/Socket.cpp',
    'Params.cpp',
    'Func.cpp',
    'Websockets/boost.cpp',
    'Websockets/zsocket.cpp',
    'Spdlog.cpp'

]

# Executable target
executable('main', src_files, dependencies: [boost, ssl,spdlog_dep])
