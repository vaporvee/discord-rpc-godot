extends Node

func _ready():
	var da = discord_sdk.activity
	da.app_id = 1099618430065324082
	da.details = "A demo activity by vaporvee#1231"
	#da.state = "Checkpoint 23/23"
	da.large_image = "game"
	da.large_image_text = "Try it now!"
	da.small_image = "boss"
	da.small_image_text = "Fighting the end boss! D:"
	da.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	print(da)
	print(discord_sdk.get_result_int())
	discord_sdk.refresh()

#	$Info.text = $Info.text.replace("{discordinfo}",str(discord_sdk.get_is_discord_working())).replace("{id}",str(discord_sdk.app_id)).replace("{details}",discord_sdk.details).replace("{state}",discord_sdk.state).replace("{lkey}",discord_sdk.large_image).replace("{ltext}",discord_sdk.large_image_text).replace("{skey}",discord_sdk.small_image).replace("{stext}",discord_sdk.small_image_text).replace("{stimestamp}",str(discord_sdk.start_timestamp)).replace("{etimestamp}",str(discord_sdk.end_timestamp))
