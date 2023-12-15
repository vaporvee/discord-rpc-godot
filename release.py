import os
from distutils.dir_util import copy_tree
import shutil

folder_path = "project/addons/discord-sdk-gd/bin/windows"

# Filter files that end with 'TMP' or 'exp' or 'lib'
matching_files = [
    file for file in os.listdir(folder_path) if file.endswith(("TMP", "exp", "lib"))
]

for file in matching_files:
    file_path = os.path.join(folder_path, file)
    os.remove(file_path)

if os.path.exists("release/ADDON-Discord-SDK-Godot/addons"):
    shutil.rmtree("release/ADDON-Discord-SDK-Godot/addons", ignore_errors=True)

copy_tree("project/addons/", "release/temp/ADDON-Discord-SDK-Godot/addons")
open(
    "release/temp/ADDON-Discord-SDK-Godot/addons/discord-sdk-gd/bin/.gdignore", "a"
).close()

shutil.make_archive("release/ADDON-Discord-SDK-Godot", "zip", "release/temp/")

shutil.rmtree("release/temp/")
