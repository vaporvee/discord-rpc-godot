import os
import shutil

os.system("git submodule update --init")

os.system("python ./src/lib/discord-rpc/build.py")

if not os.path.exists("src/lib/discord-rpc-copies/"):
    os.makedirs("src/lib/discord-rpc-copies/")

shutil.copy2(
    "src/lib/discord-rpc/builds/install/win64-dynamic/lib/discord-rpc.lib",
    "src/lib/discord-rpc-copies/",
)
shutil.copy2(
    "src/lib/discord-rpc/builds/install/win64-dynamic/bin/discord-rpc.dll",
    "src/lib/discord-rpc-copies/",
)
shutil.copy2(
    "src/lib/discord-rpc/builds/install/win32-dynamic/bin/discord-rpc.dll",
    "src/lib/discord-rpc-copies/discord-rpc_x86.dll",
)

shutil.copy2(
    "src/lib/discord-rpc/builds/install/linux-dynamic/lib/libdiscord-rpc.so",
    "src/lib/discord-rpc-copies/",
)
