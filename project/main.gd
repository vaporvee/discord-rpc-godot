extends Node

func _ready():
	discord_sdk.app_id = 1099618430065324082
	discord_sdk.details = "A demo activity by vaporvee#1231"
	discord_sdk.state = "Checkpoint 23/23"

	discord_sdk.large_image = "game"
	discord_sdk.large_image_text = "Try it now!"
	discord_sdk.small_image = "boss"
	discord_sdk.small_image_text = "Fighting the end boss! D:"
	discord_sdk.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	var my_secret = str(randi_range(0,999999))

	discord_sdk.party_id = "mylobbycanbeeverything_" + my_secret
	discord_sdk.current_party_size = 1
	discord_sdk.max_party_size = 4
	discord_sdk.match_secret = "m_" + my_secret + ",discord_sdk.current_party_size" #better use seeds with 1 to 1 range instead of just chars
	discord_sdk.join_secret = "j_" + my_secret + ",discord_sdk.current_party_size" 
	discord_sdk.spectate_secret = "s_" + my_secret
	#discord_sdk.start_timestamp = int(Time.get_unix_time_from_system())
	#discord_sdk.register_command("steam://rungameid/1389990")
	#discord_sdk.register_steam(1389990)
	discord_sdk.refresh()

func debug_text_update():
	$Info.text = $Info.text.replace("{ssecret}",discord_sdk.spectate_secret).replace("{jsecret}",discord_sdk.join_secret).replace("{msecret}",discord_sdk.match_secret).replace("{mpartysize}",str(discord_sdk.max_party_size)).replace("{cpartysize}",str(discord_sdk.current_party_size)).replace("{partyid}",discord_sdk.party_id).replace("{discordinfo}",str(discord_sdk.get_is_discord_working())).replace("{id}",str(discord_sdk.app_id)).replace("{details}",discord_sdk.details).replace("{state}",discord_sdk.state).replace("{lkey}",discord_sdk.large_image).replace("{ltext}",discord_sdk.large_image_text).replace("{skey}",discord_sdk.small_image).replace("{stext}",discord_sdk.small_image_text).replace("{stimestamp}",str(discord_sdk.start_timestamp)).replace("{etimestamp}",str(discord_sdk.end_timestamp))

func _on_activity_join_request(user_requesting):
	print(user_requesting)

func _on_activity_join(secret):
	if(discord_sdk.join_secret != secret):
		discord_sdk.current_party_size = clamp(int(secret.split(",")[1]) + 1, 0, discord_sdk.max_party_size)
		discord_sdk.party_id = secret.split(",")[0].replace("j_","mylobbycanbeeverything_")
		discord_sdk.match_secret = secret.split(",")[0].replace("j_","m_")
		discord_sdk.join_secret = secret.split(",")[0]
		discord_sdk.spectate_secret = secret.split(",")[0].replace("j_","s_")
		discord_sdk.refresh()
		$Info.text = $Info.text.replace("{ssecret}",discord_sdk.spectate_secret).replace("{jsecret}",discord_sdk.join_secret).replace("{msecret}",discord_sdk.match_secret).replace("{mpartysize}",str(discord_sdk.max_party_size)).replace("{cpartysize}",str(discord_sdk.current_party_size)).replace("{partyid}",discord_sdk.party_id).replace("{discordinfo}",str(discord_sdk.get_is_discord_working())).replace("{id}",str(discord_sdk.app_id)).replace("{details}",discord_sdk.details).replace("{state}",discord_sdk.state).replace("{lkey}",discord_sdk.large_image).replace("{ltext}",discord_sdk.large_image_text).replace("{skey}",discord_sdk.small_image).replace("{stext}",discord_sdk.small_image_text).replace("{stimestamp}",str(discord_sdk.start_timestamp)).replace("{etimestamp}",str(discord_sdk.end_timestamp))
		print(secret)
		print(discord_sdk.get_current_party_size())
		print(discord_sdk.get_join_secret())

func _on_activity_spectate(secret):
	print(secret)
