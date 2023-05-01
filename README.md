<img src="https://github.com/vaporvee/discord-sdk-godot/blob/main/project/assets/Banner_v1.png?raw=true">

[![HitCount](https://hits.dwyl.com/vaporvee/discord-sdk-godot.svg)](https://hits.dwyl.com/vaporvee/discord-sdk-godot)

### This is an early version! In future versions there will be invites, user info etc. very soon!
Don't forget to run the following command **if you clone this project** or the godot-cpp folder will be empty
```sh
git submodule update --init
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
	Discord_Activity.app_id = 1099618430065324082 # Application ID
	print("Discord working: " + str(Discord_Activity.get_is_discord_working())) # A boolean if everything worked
	Discord_Activity.details = "A demo activity by vaporvee#1231"
	Discord_Activity.state = "Checkpoint 23/23"
	
	Discord_Activity.large_image = "game" # Image key from "Art Assets"
	Discord_Activity.large_image_text = "Try it now!"
	Discord_Activity.small_image = "boss" # Image key from "Art Assets"
	Discord_Activity.small_image_text = "Fighting the end boss! D:"
	
	Discord_Activity.start_timestamp = int(Time.get_unix_time_from_system()) # "02:41 elapsed"
	# Discord_Activity.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time

	Discord_Activity.refresh() # Always refresh after changing the values!

```
#### Then it should look like this: 
<img src="https://cdn.discordapp.com/attachments/825019604207927326/1099642861256970311/activity.webp">

### [Try a built demo](https://github.com/vaporvee/discord-sdk-godot/releases/latest/download/Demo-Export.zip)
:incoming_envelope: Still questions? write an [issue](https://github.com/vaporvee/discord-sdk-godot/issues)! I'll answer very fast :)

<br />
<br />

### Credit
[@Pukimaa](https://github.com/pukimaa) - Logo Design

<br />

*This project is not endorsed or affiliated with Discord Inc. or the Godot Foundation.*
