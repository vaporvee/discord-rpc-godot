import zipfile
from distutils.dir_util import copy_tree
import shutil
import os
import sys
import urllib.request

godot_cpp_url = "https://github.com/godotengine/godot-cpp/archive/refs/tags/godot-4.1.2-stable.zip"

godot_cpp_download_path = "src/lib/godot-cpp.zip"

urllib.request.urlretrieve(godot_cpp_url, godot_cpp_download_path)

print(f"Downloaded godot-cpp to {godot_cpp_download_path}")

godot_cpp_zip_file_path = "src/lib/godot-cpp.zip"
godot_cpp_destination_dir = "src/lib/godot-cpp/"
os.makedirs(godot_cpp_destination_dir, exist_ok=True)
with zipfile.ZipFile(godot_cpp_zip_file_path, 'r') as zip_ref:
    files_to_extract = [f for f in zip_ref.namelist() if f.startswith('godot-cpp-godot-4.1.2-stable/')]
    for file in files_to_extract:
        adjusted_path = file.replace('godot-cpp-godot-4.1.2-stable/', '',  1)
        zip_ref.extract(file, godot_cpp_destination_dir + adjusted_path)
        
print("Extracted godot-cpp-godot-4.1.2-stable to src/lib/godot-cpp/")
with zipfile.ZipFile("src/lib/discord_game_sdk.zip", "r") as zip_ref:
    zip_ref.extractall("src/lib/discord_game_sdk/")
with open("src/lib/discord_game_sdk/cpp/types.h", "r+") as f:
    s = f.read()
    f.seek(0)
    f.write("#include <cstdint>\n" + s)

copy_tree("src/lib/discord_game_sdk/lib/", "src/lib/discord_game_sdk/bin/")
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
copy_tree("src/lib/discord_game_sdk/bin/aarch64/", "src/lib/discord_game_sdk/bin/")
copy_tree("src/lib/discord_game_sdk/bin/x86/", "src/lib/discord_game_sdk/bin/")
copy_tree("src/lib/discord_game_sdk/bin/x86_64/", "src/lib/discord_game_sdk/bin/")

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
    os.system("lipo src/lib/discord_game_sdk/bin/{discord_game_sdk.dylib,discord_game_sdk_aarch64.dylib} -output src/lib/discord_game_sdk/bin/libdiscord_game_sdk.dylib -create")
    # Change the install name to (library's location)/(its new name)
    os.system("install_name_tool -id '@loader_path/libdiscord_game_sdk.dylib'\
    src/lib/discord_game_sdk/bin/libdiscord_game_sdk.dylib")
    # Remove the ones it's made of
    os.remove("src/lib/discord_game_sdk/bin/discord_game_sdk.dylib")
    os.remove("src/lib/discord_game_sdk/bin/discord_game_sdk_aarch64.dylib")
