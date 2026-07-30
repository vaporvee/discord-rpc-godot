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
export_platforms = ["windows", "linux", "macos"]
for platform in export_platforms:
    os.makedirs(f"project/export/{platform}", exist_ok=True)

if shutil.which("godot"):
    os.system("cd project && godot --headless --export-release \"Linux/X11\"")
    os.system("cd project && godot --headless --export-release \"Windows Desktop\"")
    os.system("cd project && godot --headless --export-release \"macOS\"")

for platform in export_platforms:
    # macOS already exports directly to a zip, so just copy it instead of re-zipping it
    if platform == "macos":
        shutil.copyfile("project/export/macos/discord-rpc-godot-demo.zip", f"release/Demo-Export-{platform}.zip")
    else:
        shutil.make_archive(f"release/Demo-Export-{platform}", "zip", f"project/export/{platform}")
    print(f"Demo-Export-{platform}.zip has been created successfully.")
