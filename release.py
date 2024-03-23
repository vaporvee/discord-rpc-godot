import os
import shutil
from distutils.dir_util import copy_tree

win_folder_path = "project/addons/discord-rpc-gd/bin/windows"

matching_files = [file for file in os.listdir(win_folder_path) if file.endswith(("TMP", "exp", "lib"))]
for file in matching_files:
    file_path = os.path.join(win_folder_path, file)
    os.remove(file_path)

if os.path.exists("release/ADDON-Discord-RPC-Godot/addons"):
    shutil.rmtree("release/ADDON-Discord-RPC-Godot/addons", ignore_errors=True)

copy_tree("project/addons/", "release/temp/ADDON-Discord-RPC-Godot/addons")

open("release/temp/ADDON-Discord-RPC-Godot/addons/discord-RPC-gd/bin/.gdignore", "a").close()

shutil.make_archive('release/ADDON-Discord-RPC-Godot', 'zip', 'release/temp/')

shutil.rmtree("release/temp/")
# Export Demos
os.system("cd project && godot --headless --export-release \"Linux/X11\"")
os.system("cd project && godot --headless --export-release \"Windows Desktop\"")
os.system("cd project && godot --headless --export-release \"macOS\"")

temp_dir = "release/temp_export_dir"
os.makedirs(temp_dir, exist_ok=True)

for platform in ["windows", "linux", "macos"]:
    shutil.copytree(f"project/export/{platform}", os.path.join(temp_dir, platform))

shutil.make_archive('release/Demo-Export', 'zip', temp_dir)

shutil.rmtree(temp_dir)

print("ADDON-Discord-RPC-Godot.zip and Demo-Export.zip have been created successfully.")
