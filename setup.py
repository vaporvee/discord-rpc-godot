import zipfile
from distutils.dir_util import copy_tree
import shutil

with zipfile.ZipFile("src/discord-game-sdk-cpp/discord_game_sdk.zip", "r") as zip_ref:
    zip_ref.extractall("src/discord-game-sdk-cpp")

copy_tree("src/discord-game-sdk-cpp/cpp", "src/discord-game-sdk-cpp/")

shutil.rmtree("src/discord-game-sdk-cpp/c/", ignore_errors=True)
shutil.rmtree("src/discord-game-sdk-cpp/cpp/", ignore_errors=True)
shutil.rmtree("src/discord-game-sdk-cpp/csharp/", ignore_errors=True)
shutil.rmtree("src/discord-game-sdk-cpp/examples/", ignore_errors=True)
shutil.rmtree("src/discord-game-sdk-cpp/lib/", ignore_errors=True)
