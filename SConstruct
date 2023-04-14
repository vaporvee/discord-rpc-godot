#!python
import os

opts = Variables([], ARGUMENTS)

# Gets the standard flags CC, CCX, etc.
env = SConscript("godot-cpp/SConstruct")

# Define our options
opts.Add(PathVariable('target_path', 'The path where the lib is installed.', 'project/addons/discord-rpc-gd/bin'))
opts.Add(PathVariable('target_name', 'The library name.', 'discord_game_sdk', PathVariable.PathAccept))

# Local dependency paths, adapt them to your setup
discord_lib_path = "lib/discord-game-sdk"

# Updates the environment with the option variables.
opts.Update(env)

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# Check our platform specifics
if env['platform'] == "macos":
    # Set the correct library
    discord_library = 'discord_game_sdk.dylib'

elif env['platform'] in ('linuxbsd', 'linux'):
    # Set correct library
    discord_library = 'discord_game_sdk.so'

elif env['platform'] == "windows":
    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    # env.Append(ENV=os.environ)

    # Set correct library
    discord_library = 'discord_game_sdk.dll'


# make sure our binding library is properly includes
env.Append(LIBPATH=[discord_lib_path])
sources = Glob('src/discord-game-sdk-cpp/*.cpp')
env.Append(CPPPATH=['src/discord-game-sdk-cpp'])
env.Append(LIBS=[
    discord_library.replace(".dll", "")
])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=['src/'])
sources += Glob('src/*.cpp')

library = env.SharedLibrary(target="project/addons/discord-rpc-gd/bin/discord_game_sdk_binding", source=sources)
env.Depends(library, Command("project/addons/discord-rpc-gd/bin/" + discord_library, discord_lib_path + "/" + discord_library, Copy("$TARGET", "$SOURCE")))

Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))