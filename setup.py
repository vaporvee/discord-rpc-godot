#!/usr/bin/env python3
import os
import shutil
import subprocess
import sys
import zipfile
from shutil import copytree


def _compiler_has_static_libstdcpp() -> bool:
    compiler = shutil.which("g++") or shutil.which("gcc")
    if compiler is None:
        return True
    result = subprocess.run(
        [compiler, "-print-file-name=libstdc++.a"], capture_output=True, text=True
    )
    static_lib_path = result.stdout.strip()
    return bool(static_lib_path) and static_lib_path != "libstdc++.a" and os.path.isfile(static_lib_path)


def _disable_static_cpp_linking() -> None:
    custom_py_path = os.path.join("src", "lib", "godot-cpp", "custom.py")
    with open(custom_py_path, "a") as f:
        f.write("use_static_cpp = False\n")
    print(f"Disabled static libstdc++ linking in {custom_py_path}")


def ensure_static_libstdcpp() -> None:
    if not sys.platform.startswith("linux"):
        return
    if _compiler_has_static_libstdcpp():
        return

    print("libstdc++.a not found")
    if shutil.which("brew"):
        os.system("brew install gcc")
        if _compiler_has_static_libstdcpp():
            return
    else:
        print("install libstdc++-static (Fedora/RHEL) or gcc (Arch) manually")

    _disable_static_cpp_linking()


ensure_static_libstdcpp()

with zipfile.ZipFile("src/lib/discord_game_sdk.zip", "r") as zip_ref:
    zip_ref.extractall("src/lib/discord_game_sdk/")

# Patch the SDK to actually build, since it's missing an include
with open("src/lib/discord_game_sdk/cpp/types.h", "r+") as f:
    s = f.read()
    f.seek(0)
    f.write("#include <cstdint>\n" + s)

# Patch the SDKs Windows.h include to lowercase, since mingw-w64 installs
# it as windows.h and Linux filesystems are case-sensitive
for header in ("cpp/ffi.h", "cpp/types.h"):
    header_path = os.path.join("src/lib/discord_game_sdk", header)
    with open(header_path, "r") as f:
        s = f.read()
    with open(header_path, "w") as f:
        f.write(s.replace("#include <Windows.h>", "#include <windows.h>"))

copytree(
    "src/lib/discord_game_sdk/lib/", "src/lib/discord_game_sdk/bin/", dirs_exist_ok=True
)
os.rename(
    "src/lib/discord_game_sdk/bin/aarch64/discord_game_sdk.dylib",
    "src/lib/discord_game_sdk/bin/aarch64/discord_game_sdk_aarch64.dylib",
)
os.rename(
    "src/lib/discord_game_sdk/bin/x86_64/discord_game_sdk.so",
    "src/lib/discord_game_sdk/bin/x86_64/libdiscord_game_sdk.so",
)
os.rename(
    "src/lib/discord_game_sdk/bin/x86/discord_game_sdk.dll",
    "src/lib/discord_game_sdk/bin/x86/discord_game_sdk_x86.dll",
)

os.rename(
    "src/lib/discord_game_sdk/bin/x86_64/discord_game_sdk.dll.lib",
    "src/lib/discord_game_sdk/bin/x86_64/discord_game_sdk.lib",
)
copytree(
    "src/lib/discord_game_sdk/bin/aarch64/",
    "src/lib/discord_game_sdk/bin/",
    dirs_exist_ok=True,
)
copytree(
    "src/lib/discord_game_sdk/bin/x86/",
    "src/lib/discord_game_sdk/bin/",
    dirs_exist_ok=True,
)
copytree(
    "src/lib/discord_game_sdk/bin/x86_64/",
    "src/lib/discord_game_sdk/bin/",
    dirs_exist_ok=True,
)

shutil.rmtree("src/lib/discord_game_sdk/c/", ignore_errors=True)
shutil.rmtree("src/lib/discord_game_sdk/csharp/", ignore_errors=True)
shutil.rmtree("src/lib/discord_game_sdk/examples/", ignore_errors=True)
shutil.rmtree("src/lib/discord_game_sdk/lib/", ignore_errors=True)
shutil.rmtree("src/lib/discord_game_sdk/bin/aarch64/", ignore_errors=True)
shutil.rmtree("src/lib/discord_game_sdk/bin/x86/", ignore_errors=True)
shutil.rmtree("src/lib/discord_game_sdk/bin/x86_64/", ignore_errors=True)
os.remove("src/lib/discord_game_sdk/README.md")

if sys.platform == "darwin":
    # Combine the two libraries into one
    os.system(
        "lipo src/lib/discord_game_sdk/bin/{discord_game_sdk.dylib,discord_game_sdk_aarch64.dylib} -output src/lib/discord_game_sdk/bin/libdiscord_game_sdk.dylib -create"
    )
    # Change the install name to (library's location)/(its new name)
    os.system(
        "install_name_tool -id '@loader_path/libdiscord_game_sdk.dylib'\
    src/lib/discord_game_sdk/bin/libdiscord_game_sdk.dylib"
    )
    # Remove the ones it's made of
    os.remove("src/lib/discord_game_sdk/bin/discord_game_sdk.dylib")
    os.remove("src/lib/discord_game_sdk/bin/discord_game_sdk_aarch64.dylib")

os.system("git submodule update --init --remote")
