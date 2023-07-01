env = Environment(
    CPPPATH='include/',
    LIBS=['glfw', 'GL']
)

env.Program('monke-dev', ['main.cpp',
                           Glob('src/core/*.cpp'),
                           Glob('src/external/*.cpp'),
                           Glob('src/types/*.cpp'),
                           Glob('include/monke/external/imgui/*.cpp')]);