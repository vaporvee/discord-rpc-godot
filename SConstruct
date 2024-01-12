#!python
import os

env = SConscript("src/lib/godot-cpp/SConstruct")

if env["platform"] == "macos":
    discord_library = "discord_game_sdk.dylib"
    discord_library_second = "discord_game_sdk_aarch64.dylib"
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

if env.get("arch") == "arm64":
    armsuffix = "_arm64"
else:
    armsuffix = ""

env.Append(LIBPATH=["src/lib/discord_game_sdk/bin/"])
sources = Glob("src/lib/discord_game_sdk/cpp/*.cpp")
env.Append(CPPPATH=["src/lib/discord_game_sdk/cpp/"])
env.Append(LIBS=["discord_game_sdk"])

env.Append(CPPPATH=["src/"])
sources += Glob("src/*.cpp")

env.Append(CPPDEFINES=["HOT_RELOAD_ENABLED"])

library = env.SharedLibrary(
    target="project/addons/discord-sdk-gd/bin/"
    + libexportfolder
    + "discord_game_sdk_binding"
    + armsuffix
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
if discord_library_second != "":
    env.Depends(
        library,
        Command(
            "project/addons/discord-sdk-gd/bin/"
            + libexportfolder
            + discord_library_second,
            "src/lib/discord_game_sdk/bin/" + discord_library_second,
            Copy("$TARGET", "$SOURCE"),
        ),
    )

Default(library)
