extends Node

# 1. Put the addons/ folder in your Godot project
# 2. Enable the addon in your Project Settings under "Plugins" and "DiscordSDK". (if it doesn't show up restart your project and try again)
# 3. Restart your project
# 4. Create an Application under https://discord.com/developers/applications and get the Application ID
# 5. (optional) Set images under "Rich Presence" and "Art Assets" and remember the keys

#SELECT THE TEXT WITH YOUR MOUSE AND CTR + K TO UNCOMMENT THE FOLLOWING

#func _ready():
#	discord_sdk.app_id = 1099618430065324082 # Application ID
#	print("Discord working: " + str(discord_sdk.get_is_discord_working())) # A boolean if everything worked
#	discord_sdk.details = "A demo activity by vaporvee#1231"
#	discord_sdk.state = "Checkpoint 23/23"
#
#	discord_sdk.large_image = "game" # Image key from "Art Assets"
#	discord_sdk.large_image_text = "Try it now!"
#	discord_sdk.small_image = "boss" # Image key from "Art Assets"
#	discord_sdk.small_image_text = "Fighting the end boss! D:"
#
#	discord_sdk.start_timestamp = int(Time.get_unix_time_from_system()) # "02:41 elapsed"
#	discord_sdk.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
#
#	discord_sdk.refresh() # Always refresh after changing the values!
