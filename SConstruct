#!python
import os

# Gets the standard flags CC, CCX, etc.
env = SConscript("src/lib/godot-cpp/SConstruct")

# Check our platform specifics
if env["platform"] == "macos":
    discord_library = "libdiscord_game_sdk.dylib"
    discord_library_second = "libdiscord_game_sdk_aarch64.dylib"
    libexportfolder = "/macos/"

elif env["platform"] in ("linuxbsd", "linux"):
    discord_library = "libdiscord_game_sdk.so"
    discord_library_second = ""
    libexportfolder = "/linux/"

elif env["platform"] == "windows":
    discord_library = "discord_game_sdk.dll"
    discord_library_second = "discord_game_sdk_x86.dll"
    libexportfolder = "/windows/"

if env["target"] == "template_debug":
    debugsuffix = "_debug"
else:
    debugsuffix = ""

# make sure our binding library is properly includes
env.Append(LIBPATH=["src/lib/discord_game_sdk/bin/"])
sources = Glob("src/lib/discord_game_sdk/cpp/*.cpp")
env.Append(CPPPATH=["src/lib/discord_game_sdk/cpp/"])  # this line for some reason doesn't get understanded by most linux distros
env.Append(LIBS=["discord_game_sdk"])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources += Glob("src/*.cpp")

# The finished exports
library = env.SharedLibrary(
    target="project/addons/discord-sdk-gd/bin/"
    + libexportfolder
    + "discord_game_sdk_binding"
    + debugsuffix,
    source=sources,
)
env.Depends(
    library,
    Command(
        "project/addons/discord-sdk-gd/bin/" + libexportfolder + discord_library,
        "src/lib/discord_game_sdk/bin/" + discord_library,
        Copy("$TARGET", "$SOURCE"),
    ),
)
if(discord_library_second != ""):
    env.Depends(
        library,
        Command(
            "project/addons/discord-sdk-gd/bin/" + libexportfolder + discord_library_second,
            "src/lib/discord_game_sdk/bin/" + discord_library_second,
            Copy("$TARGET", "$SOURCE"),
        ),
    )

Default(library)
