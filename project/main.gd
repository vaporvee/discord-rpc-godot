extends Node

func _ready():
#	discord_rpc.debug()
	
	discord_rpc.app_id = 1099618430065324082
	discord_rpc.details = "A demo activity by vaporvee#1231"
	discord_rpc.state = "Checkpoint 23/23"

	discord_rpc.large_image = "game"
	discord_rpc.large_image_text = "Try it now!"
	discord_rpc.small_image = "boss"
	discord_rpc.small_image_text = "Fighting the end boss! D:"
	discord_rpc.first_button_text = "Test from GDScript"
	discord_rpc.first_button_url = "https://github.com/vaporvee/discord-sdk-godot"
	discord_rpc.second_button_text = "🗿🗿🗿🗿🗿🗿🗿🗿🗿🗿🗿"
	discord_rpc.second_button_url = "https://www.youtube.com/watch?v=eaDeTV-LLYA"

	# discord_rpc.start_timestamp = int(Time.get_unix_time_from_system())
	discord_rpc.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time

	discord_rpc.refresh()

	$Info.text = $Info.text.replace("{id}",str(discord_rpc.app_id)).replace("{details}",discord_rpc.details).replace("{state}",discord_rpc.state).replace("{lkey}",discord_rpc.large_image).replace("{ltext}",discord_rpc.large_image_text).replace("{skey}",discord_rpc.small_image).replace("{stext}",discord_rpc.small_image_text).replace("{stimestamp}",str(discord_rpc.start_timestamp)).replace("{etimestamp}",str(discord_rpc.end_timestamp))
