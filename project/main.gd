extends Node

func _ready():
	#Discord_SDK.debug()
	Discord_SDK.app_id = 1099618430065324082
	Discord_SDK.details = "A demo activity by vaporvee#1231"
	Discord_SDK.state = "Checkpoint 23/23"
	
	Discord_SDK.large_image = "game"
	Discord_SDK.large_image_text = "Try it now!"
	Discord_SDK.small_image = "boss"
	Discord_SDK.small_image_text = "Fighting the end boss! D:"
	
	#Discord_SDK.start_timestamp = int(Time.get_unix_time_from_system())
	Discord_SDK.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time

	Discord_SDK.refresh()
	
	$Info.text = $Info.text.replace("{discordinfo}",str(Discord_SDK.get_is_discord_working())).replace("{id}",str(Discord_SDK.app_id)).replace("{details}",Discord_SDK.details).replace("{state}",Discord_SDK.state).replace("{lkey}",Discord_SDK.large_image).replace("{ltext}",Discord_SDK.large_image_text).replace("{skey}",Discord_SDK.small_image).replace("{stext}",Discord_SDK.small_image_text).replace("{stimestamp}",str(Discord_SDK.start_timestamp)).replace("{etimestamp}",str(Discord_SDK.end_timestamp))
