extends Node

func _ready():
	discord_sdk.app_id = 1099618430065324082
	discord_sdk.details = "A demo activity by vaporvee#1231"
	discord_sdk.state = "Checkpoint 23/23"
	
	discord_sdk.large_image = "game"
	discord_sdk.large_image_text = "Try it now!"
	discord_sdk.small_image = "boss"
	discord_sdk.small_image_text = "Fighting the end boss! D:"
	
	discord_sdk.party_id = "my-random-id-can-be-everything"
	discord_sdk.current_party_size = 1
	discord_sdk.max_party_size = 4
	discord_sdk.match_secret = "my-random-match-secret"
	discord_sdk.join_secret = "my-random-join-secret"
	discord_sdk.spectate_secret = "my-random-spectate-secret"
	
	#discord_sdk.start_timestamp = int(Time.get_unix_time_from_system())
	discord_sdk.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	discord_sdk.refresh()
	
	$Info.text = $Info.text.replace("{discordinfo}",str(discord_sdk.get_is_discord_working())).replace("{id}",str(discord_sdk.app_id)).replace("{details}",discord_sdk.details).replace("{state}",discord_sdk.state).replace("{lkey}",discord_sdk.large_image).replace("{ltext}",discord_sdk.large_image_text).replace("{skey}",discord_sdk.small_image).replace("{stext}",discord_sdk.small_image_text).replace("{stimestamp}",str(discord_sdk.start_timestamp)).replace("{etimestamp}",str(discord_sdk.end_timestamp))
