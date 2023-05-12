<img src="/project/assets/Banner.svg" alt="Project Banner" />

![HitCount](https://hits.dwyl.com/vaporvee/discord-sdk-godot.svg)

### :warning: This is an early version! MacOS support still doesn't work! In future versions there also will be invites, user info etc. very soon!
Don't forget to run the following command **if you clone this project** or files will be missing

```sh
python setup.py
```
# Addon Usage :rocket:
1. [Download the addon](https://github.com/vaporvee/discord-sdk-godot/releases/latest/download/ADDON-Discord-SDK-Godot.zip/)
2. Put the `addons/` folder in your Godot project
3. Enable the addon in your Project Settings under "Plugins" and "DiscordSDK". (if it doesn't show up restart  your project and try again)
4. Restart your project
5. Create an Application under https://discord.com/developers/applications and get the Application ID
6. (optional) Set images under "Rich Presence" and "Art Assets" and remember the keys
```gdscript
extends Node

func _ready():
	discord_sdk.app_id = 1099618430065324082 # Application ID
	print("Discord working: " + str(discord_sdk.get_is_discord_working())) # A boolean if everything worked
	discord_sdk.details = "A demo activity by vaporvee#1231"
	discord_sdk.state = "Checkpoint 23/23"
	
	discord_sdk.large_image = "game" # Image key from "Art Assets"
	discord_sdk.large_image_text = "Try it now!"
	discord_sdk.small_image = "boss" # Image key from "Art Assets"
	discord_sdk.small_image_text = "Fighting the end boss! D:"

	discord_sdk.start_timestamp = int(Time.get_unix_time_from_system()) # "02:46 elapsed"
	# discord_sdk.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time / "01:00 remaining"

	discord_sdk.refresh() # Always refresh after changing the values!

```
#### Then it will look similar to this: 
<img src="/project/assets/ActivityPreview.svg" alt="Activity Preview" />

### [Try a built demo](https://github.com/vaporvee/discord-sdk-godot/releases/latest/download/Demo-Export.zip)
:incoming_envelope: Still questions? write an [issue](https://github.com/vaporvee/discord-sdk-godot/issues)! I'll answer very fast :)

<br />
<br />

### Credit
[@Pukimaa](https://github.com/pukimaa) - Designer<br>
[@koyuawsmbrtn](https://github.com/koyuawsmbrtn) - Getting it to work on MacOS (shes giving her best)
<br />

*This project is not endorsed or affiliated with Discord Inc. or the Godot Foundation.*
