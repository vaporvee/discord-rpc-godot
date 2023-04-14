import os
import platform

if platform.system() == "Windows":
    for file in os.listdir("project/addons/discord-rpc-gd/bin/"):
        if file.endswith(".exp"):
            os.remove(os.path.join("project/addons/discord-rpc-gd/bin/", file))
    for file in os.listdir("project/addons/discord-rpc-gd/bin/"):
        if file.endswith(".lib"):
            os.remove(os.path.join("project/addons/discord-rpc-gd/bin/", file))