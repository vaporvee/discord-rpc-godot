#!/usr/bin/python3
import os

# Gets the standard flags CC, CCX, etc.
env = SConscript("lib/godot-cpp/SConstruct")

# Check our platform specifics
if env['platform'] == "macos":
    discord_library = 'libdiscord_game_sdk.dylib'
    libexportfolder = "/macos/"

elif env['platform'] in ('linuxbsd', 'linux'):
    discord_library = 'libdiscord_game_sdk.so'
    libexportfolder = "/linux/"

elif env['platform'] == "windows":
    discord_library = 'discord_game_sdk.dll'
    libexportfolder = "/windows/"

if env['target'] == "template_debug":
    debugsuffix = "_debug"
else:
    debugsuffix = ""

# make sure our binding library is properly includes
env.Append(LIBPATH=["lib/discord-game-sdk/"])
sources = Glob('src/discord-game-sdk-cpp/*.cpp')
env.Append(CPPPATH=['src/discord-game-sdk-cpp'])
env.Append(LIBS=["discord_game_sdk"])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=['src/'])
sources += Glob('src/*.cpp')

# The finished exports
library = env.SharedLibrary(target="project/addons/discord-sdk-gd/bin/" +
                            libexportfolder + "discord_game_sdk_binding" + debugsuffix, source=sources)
env.Depends(library, Command("project/addons/discord-sdk-gd/bin/" + libexportfolder +
            discord_library, "lib/discord-game-sdk/" + discord_library, Copy("$TARGET", "$SOURCE")))

Default(library)
