import zipfile
import os
import re
import shutil

EXPECTED_VERSION = "1.0.7445"

# Extract the version from the zip filename
zip_path = "src/lib/DiscordSocialSdk-1.0.7445.zip"
match = re.search(r"DiscordSocialSdk-(\d+\.\d+\.\d+)\.zip", zip_path)
if match:
    extracted_version = match.group(1)
    if extracted_version != EXPECTED_VERSION:
        print(f"Warning: Last tested version {EXPECTED_VERSION}, but found {extracted_version} in the zip file.")

# Extract the zip file ignoring the version in the filename
with zipfile.ZipFile(zip_path, "r") as zip_ref:
    zip_ref.extractall("src/lib/")

# Copy the release DLL to the lib directory
release_dll_src = "src/lib/discord_social_sdk/bin/release/discord_partner_sdk.dll"
release_dll_dest = "src/lib/discord_social_sdk/lib/release/"
os.makedirs(release_dll_dest, exist_ok=True)
shutil.copy(release_dll_src, release_dll_dest)

# Copy the debug DLL to the lib/debug directory
debug_dll_src = "src/lib/discord_social_sdk/bin/debug/discord_partner_sdk.dll"
debug_dll_dest = "src/lib/discord_social_sdk/lib/debug/"
os.makedirs(debug_dll_dest, exist_ok=True)
shutil.copy(debug_dll_src, debug_dll_dest)

# Delete the bin folder
bin_folder = "src/lib/discord_social_sdk/bin"
shutil.rmtree(bin_folder, ignore_errors=True)

os.system("git submodule update --init --remote")
