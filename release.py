#!/usr/bin/env python3
import os
import shutil
from shutil import copytree

win_folder_path = "project/addons/discord-rpc-gd/bin/windows"

matching_files = [file for file in os.listdir(win_folder_path) if file.endswith(("TMP", "exp", "lib"))]
for file in matching_files:
    file_path = os.path.join(win_folder_path, file)
    os.remove(file_path)

if os.path.exists("release/ADDON-Discord-RPC-Godot/addons"):
    shutil.rmtree("release/ADDON-Discord-RPC-Godot/addons", ignore_errors=True)

copytree("project/addons/", "release/temp/ADDON-Discord-RPC-Godot/addons", dirs_exist_ok=True)

open("release/temp/ADDON-Discord-RPC-Godot/addons/discord-rpc-gd/bin/.gdignore", "a").close()

shutil.make_archive('release/ADDON-Discord-RPC-Godot', 'zip', 'release/temp/')

shutil.rmtree("release/temp/")
print("ADDON-Discord-RPC-Godot.zip has been created successfully.")

# Export Demos
if shutil.which("godot"):
    os.system("cd project && godot --headless --export-release \"Linux/X11\"")
    os.system("cd project && godot --headless --export-release \"Windows Desktop\"")
    os.system("cd project && godot --headless --export-release \"macOS\"")

export_platforms = [p for p in ["windows", "linux", "macos"] if os.path.isdir(f"project/export/{p}")]
if export_platforms:
    temp_dir = "release/temp_export_dir"
    os.makedirs(temp_dir, exist_ok=True)
    for platform in export_platforms:
        shutil.copytree(f"project/export/{platform}", os.path.join(temp_dir, platform))
    shutil.make_archive('release/Demo-Export', 'zip', temp_dir)
    shutil.rmtree(temp_dir)
    print("Demo-Export.zip has been created successfully.")
else:
    print("Skipping demo export: no export directories found.")
