#!python
import os

env = SConscript("src/lib/godot-cpp/SConstruct")

env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    discord_library = "libdiscord_partner_sdk.dylib"
    libexportfolder = "/macos/"

elif env["platform"] in ("linuxbsd", "linux"):
    discord_library = "libdiscord_partner_sdk.so"
    libexportfolder = "/linux/"

elif env["platform"] == "windows":
    discord_library = "discord_partner_sdk.dll"
    libexportfolder = "/windows/"

if env["target"] == "template_debug":
    debugsuffix = "_debug"
else:
    debugsuffix = ""

env.Append(LIBPATH=["src/lib/discord_social_sdk/lib/release/"])
env.Append(LIBS=["discord_partner_sdk"])

env.Append(CPPDEFINES=["HOT_RELOAD_ENABLED"])

library = env.SharedLibrary(
    target="project/addons/discord-rpc-gd/bin/"
    + libexportfolder
    + "discord_partner_sdk_binding"
    + debugsuffix,
    source=sources,
)
env.Depends(
    library,
    Command(
        "project/addons/discord-rpc-gd/bin/" + libexportfolder + discord_library,
        "src/lib/discord_social_sdk/lib/release/" + discord_library,
        Copy("$TARGET", "$SOURCE"),
    ),
)

Default(library)
