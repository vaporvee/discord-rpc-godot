#!python
import os

# Gets the standard flags CC, CCX, etc.
env = SConscript("src/lib/godot-cpp/SConstruct")

# Check our platform specifics
if env["platform"] == "macos":
    discord_library = "libdiscord-rpc.dylib"
    discord_library_second = ""
    libexportfolder = "/macos/"

elif env["platform"] in ("linuxbsd", "linux"):
    discord_library = "libdiscord-rpc.so"
    discord_library_second = ""
    libexportfolder = "/linux/"

elif env["platform"] == "windows":
    discord_library = "discord-rpc.dll"
    discord_library_second = "discord-rpc_x86.dll"
    libexportfolder = "/windows/"

if env["target"] == "template_debug":
    debugsuffix = "_debug"
else:
    debugsuffix = ""

# make sure our binding library is properly includes
env.Append(LIBPATH=["src/lib/discord-rpc-copies"])
env.Append(LIBS=["discord-rpc"])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

# The finished exports
library = env.SharedLibrary(
    target="project/addons/discord-rpc-gd/bin/"
    + libexportfolder
    + "discord-rpc_binding"
    + debugsuffix,
    source=sources,
)
env.Depends(
    library,
    Command(
        "project/addons/discord-rpc-gd/bin/" + libexportfolder + discord_library,
        "src/lib/discord-rpc-copies/" + discord_library,
        Copy("$TARGET", "$SOURCE"),
    ),
)

Default(library)
