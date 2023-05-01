extends Node

# 1. Put the addons/ folder in your Godot project
# 2. Enable the addon in your Project Settings under "Plugins" and "DiscordSDK". (if it doesn't show up restart your project and try again)
# 3. Restart your project
# 4. Create an Application under https://discord.com/developers/applications and get the Application ID
# 5. (optional) Set images under "Rich Presence" and "Art Assets" and remember the keys

func _ready():
	DiscordSDK.app_id = 1099618430065324082 # Application ID
	print("Discord status: " + DiscordSDK.get_sdk_info()) # Returns "Ok" if everything worked
	DiscordSDK.details = "A demo activity by vaporvee#1231"
	DiscordSDK.state = "Checkpoint 23/23"
	
	DiscordSDK.large_image = "game" # Image key from "Art Assets"
	DiscordSDK.large_image_text = "Try it now!"
	DiscordSDK.small_image = "boss" # Image key from "Art Assets"
	DiscordSDK.small_image_text = "Fighting the end boss! D:"
	
	DiscordSDK.start_timestamp = int(Time.get_unix_time_from_system()) # "02:41 elapsed"
	# Discord_Activity.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	DiscordSDK.refresh() # Always refresh after changing the values!
