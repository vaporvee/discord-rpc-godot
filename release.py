import os
from distutils.dir_util import copy_tree
import shutil

if os.path.exists("release/ADDON-Discord-SDK-Godot/addons"):
    shutil.rmtree("release/ADDON-Discord-SDK-Godot/addons", ignore_errors=True)

copy_tree("project/addons/", "release/temp/ADDON-Discord-SDK-Godot/addons")

shutil.make_archive("release/ADDON-Discord-SDK-Godot", "zip", "release/temp/")

shutil.rmtree("release/temp/")
