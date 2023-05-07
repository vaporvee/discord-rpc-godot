import zipfile
from distutils.dir_util import copy_tree
import shutil
import os

os.system("python ./src/lib/discord-rpc/build.py")

os.system("git submodule update --init")
