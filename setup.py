import zipfile
import os
import re
import shutil
import sys
import glob

EXPECTED_VERSION = "1.0.7445"

zip_files = glob.glob("src/lib/DiscordSocialSdk-*.zip")
if not zip_files:
    print("Error: No zip file matching 'DiscordSocialSdk-*.zip' found.")
    sys.exit(1)

zip_path = zip_files[0]  # Use the first matching file
match = re.search(r"DiscordSocialSdk-(\d+\.\d+\.\d+)\.zip", zip_path)
if match:
    extracted_version = match.group(1)
    if extracted_version != EXPECTED_VERSION:
        print(f"Warning: Last tested version {EXPECTED_VERSION}, but found {extracted_version} in the zip file.")
print(f"Extracting {zip_path}...")

# Extract the zip file ignoring the version in the filename
with zipfile.ZipFile(zip_path, "r") as zip_ref:
    zip_ref.extractall("src/lib/")

release_dll_src = "src/lib/discord_social_sdk/bin/release/discord_partner_sdk.dll"
release_dll_dest = "src/lib/discord_social_sdk/lib/release/"
os.makedirs(release_dll_dest, exist_ok=True)
shutil.copy(release_dll_src, release_dll_dest)

debug_dll_src = "src/lib/discord_social_sdk/bin/debug/discord_partner_sdk.dll"
debug_dll_dest = "src/lib/discord_social_sdk/lib/debug/"
os.makedirs(debug_dll_dest, exist_ok=True)
shutil.copy(debug_dll_src, debug_dll_dest)

include_folder_src = "src/lib/discord_social_sdk/include"
include_folder_dest = "src"
shutil.copytree(include_folder_src, include_folder_dest, dirs_exist_ok=True)

shutil.rmtree(include_folder_src, ignore_errors=True)

bin_folder = "src/lib/discord_social_sdk/bin"
shutil.rmtree(bin_folder, ignore_errors=True)

print(f"Extracted and copied Discord Social SDK version: {extracted_version}")

print("Getting submodules...")
os.system("git submodule update --init --remote")
print("Finished setup!")
