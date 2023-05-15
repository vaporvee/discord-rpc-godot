extends Node

var invite_pfp

func _ready():
	set_activity()
	discord_sdk.connect("activity_join_request",_on_activity_join_request)
	discord_sdk.connect("activity_join",_on_activity_join)
	discord_sdk.connect("activity_spectate",_on_activity_spectate)
	download_texture("https://cdn.discordapp.com/embed/avatars/1.png", "res://discord_pfp_cache/invitepfp.png")
	debug_text_update()
func download_texture(url, file_name):
	$user_request_avatar/HTTPRequest.download_file = file_name
	invite_pfp = file_name
	$user_request_avatar/HTTPRequest.request(url)

func _on_http_request_request_completed(_result, _response_code, _headers, _body):
	var image = Image.new()
	image.load(str(invite_pfp))
	var texture = ImageTexture.create_from_image(image)
	$user_request_avatar.texture = texture

func set_activity():
	discord_sdk.app_id = 1099618430065324082
	discord_sdk.details = "A demo activity by vaporvee#1231"
	discord_sdk.state = "Checkpoint 23/23"
	
	discord_sdk.large_image = "example_game"
	discord_sdk.large_image_text = "Try it now!"
	discord_sdk.small_image = "boss"
	discord_sdk.small_image_text = "Fighting the end boss! D:"
	discord_sdk.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	print(discord_sdk.get_is_overlay_enabled())
	
	# It is NOT recommended to manage secrets locally! It's meant to be a payload wich the server 
	# understands and returns the other variables like current_party_size, party_id etc. Most of the values must differ from the others.
	var my_secret = str(randi_range(0,999999))
	
	discord_sdk.party_id = "mylobbycanbeeverything_" + my_secret
	discord_sdk.current_party_size = 1
	discord_sdk.max_party_size = 4
	discord_sdk.match_secret = "m_" + my_secret #better use seeds with 1 to 1 range instead of just chars
	discord_sdk.join_secret = "j_" + my_secret
	discord_sdk.spectate_secret = "s_" + my_secret
	discord_sdk.is_public_party = true
	discord_sdk.instanced = true #required for spectate
	#discord_sdk.start_timestamp = int(Time.get_unix_time_from_system())
	discord_sdk.register_command("C:\\Users\\yanni\\Desktop\\demo\\discord_sdk.exe")
	#discord_sdk.register_steam(1389990)
	discord_sdk.refresh()

func debug_text_update():
	$Info.text = $Info.text.replace("{ssecret}",discord_sdk.spectate_secret).replace("{jsecret}",discord_sdk.join_secret).replace("{msecret}",discord_sdk.match_secret).replace("{mpartysize}",str(discord_sdk.max_party_size)).replace("{cpartysize}",str(discord_sdk.current_party_size)).replace("{partyid}",discord_sdk.party_id).replace("{discordinfo}",str(discord_sdk.get_is_discord_working())).replace("{id}",str(discord_sdk.app_id)).replace("{details}",discord_sdk.details).replace("{state}",discord_sdk.state).replace("{lkey}",discord_sdk.large_image).replace("{ltext}",discord_sdk.large_image_text).replace("{skey}",discord_sdk.small_image).replace("{stext}",discord_sdk.small_image_text).replace("{stimestamp}",str(discord_sdk.start_timestamp)).replace("{etimestamp}",str(discord_sdk.end_timestamp))

var user_request = {};

func _on_activity_join_request(user_requesting):
	print(user_requesting)
	user_request = user_requesting
	print(user_requesting.avatar_url)
	download_texture(user_requesting.avatar_url, "res://discord_pfp_cache/invitepfp.png")

func _on_activity_join(secret):
	if(discord_sdk.join_secret != secret):
		discord_sdk.current_party_size = clamp(int(secret) + 1, 0, discord_sdk.max_party_size)
		discord_sdk.party_id = secret.replace("j_","mylobbycanbeeverything_")
		discord_sdk.match_secret = secret.replace("j_","m_")
		discord_sdk.join_secret = secret
		discord_sdk.spectate_secret = secret.replace("j_","s_")
		discord_sdk.refresh()
		$Info.text = $Info.text.replace("{ssecret}",discord_sdk.spectate_secret).replace("{jsecret}",discord_sdk.join_secret).replace("{msecret}",discord_sdk.match_secret).replace("{mpartysize}",str(discord_sdk.max_party_size)).replace("{cpartysize}",str(discord_sdk.current_party_size)).replace("{partyid}",discord_sdk.party_id).replace("{discordinfo}",str(discord_sdk.get_is_discord_working())).replace("{id}",str(discord_sdk.app_id)).replace("{details}",discord_sdk.details).replace("{state}",discord_sdk.state).replace("{lkey}",discord_sdk.large_image).replace("{ltext}",discord_sdk.large_image_text).replace("{skey}",discord_sdk.small_image).replace("{stext}",discord_sdk.small_image_text).replace("{stimestamp}",str(discord_sdk.start_timestamp)).replace("{etimestamp}",str(discord_sdk.end_timestamp))
		debug_text_update()

func _on_activity_spectate(secret):
	print(secret)

func _on_check_button_toggled(button_pressed):
	if(button_pressed):
		set_activity()
	else:
		discord_sdk.clear()

func _on_button_pressed():
	if(!user_request.is_empty()):
		discord_sdk.accept_join_request(user_request.id)

func _on_line_edit_text_submitted(new_text):
	discord_sdk.send_invite(int(new_text),true,"this is a test invite sent from godot")
	print(int(new_text))


func _on_line_edit_2_text_submitted(new_text):
	discord_sdk.accept_invite(int(new_text))
	print(int(new_text))
