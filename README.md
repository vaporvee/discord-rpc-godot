<img src="https://github.com/vaporvee/discord-sdk-godot/blob/main/project/assets/Banner_v1.png?raw=true">

### This is an early version! In future versions there will be lobbies, invites, linux builds etc. very soon!
Don't forget to run the following command **if you clone this project** or the godot-cpp folder will be empty
```sh
git submodule update --init
```
# Addon Usage :rocket:
1. [Download the addon](https://github.com/vaporvee/discord-sdk-godot/releases/latest/download/ADDON-Discord-SDK-Godot.zip/)
2. Put the `discord-sdk-gd/` folder in a `addons/` folder in your Godot project
3. Enable the addon in your Project Settings under "Plugins" and "DiscordSDK". (if it doesn't show up reopen the project)
4. Create an Application under https://discord.com/developers/applications and get the Application ID
5. (optional) Set images under "Rich Presence" and "Art Assets" and remember the keys
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
	#Discord_Activity.end_timestamp = 2492978400 # "15:41 left" (but currently 31. 12. 2048 in unix time)

	Discord_Activity.refresh() # Always refresh after changing the values!

```
#### Then it should look like this: 
<img src="https://cdn.discordapp.com/attachments/825019604207927326/1099642861256970311/activity.webp">

### [Try a built demo](https://github.com/vaporvee/discord-sdk-godot/releases/latest/download/Demo-Export.zip)
:incoming_envelope: Still questions? write an [issue](https://github.com/vaporvee/discord-sdk-godot/issues)! I'll answer very fast :)

<br />

## Extra Info
- The Discord SDK itself doesn't build under Linux for some reason (I don't have a Mac so i don't even know if it's builds under OSX) its not well documented but I try as hard as i can to get it working crossplatform but at the time its only working under Windows... (But feel free to make pull requests btw)
- Its an early release some features aren't implemented only because i need a small amount of time not because it's not possible

<br />
<br />

### Credit
[@Pukimaa](https://github.com/pukimaa) - Logo Design

<br />

*This project is not endorsed or affiliated with Discord Inc. or the Godot Foundation.*
