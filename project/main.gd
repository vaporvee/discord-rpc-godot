extends Node

func _ready() -> void:
	print(discord_sdk.get_current_user())
	set_activity()
	discord_sdk.connect("activity_join_request",_on_activity_join_request)
	discord_sdk.connect("activity_join",_on_activity_join)
	discord_sdk.connect("activity_spectate",_on_activity_spectate)

func set_activity() -> void:
	discord_sdk.clear()
	discord_sdk.app_id = 1099618430065324082
	discord_sdk.details = "A demo activity by vaporvee#1231"
	discord_sdk.state = "Checkpoint 23/23"
	
	discord_sdk.large_image = "example_game"
	discord_sdk.large_image_text = "Try it now!"
	discord_sdk.small_image = "boss"
	discord_sdk.small_image_text = "Fighting the end boss! D:"
	discord_sdk.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	# It is NOT recommended to manage secrets locally! It's meant to be a payload wich the server 
	# understands and returns the other variables like current_party_size, party_id etc. Most of the values must differ from the others.
	var my_secret: String = str(randi_range(0,999999))
	
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

var user_request: Dictionary;

func _on_activity_join_request(user_requesting) -> void:
	print(user_requesting)
	user_request = user_requesting

func _on_activity_join(secret) -> void:
	if(discord_sdk.join_secret != secret):
		discord_sdk.current_party_size = clamp(int(secret) + 1, 0, discord_sdk.max_party_size)
		discord_sdk.party_id = secret.replace("j_","mylobbycanbeeverything_")
		discord_sdk.match_secret = secret.replace("j_","m_")
		discord_sdk.join_secret = secret
		discord_sdk.spectate_secret = secret.replace("j_","s_")
		discord_sdk.refresh()

func _on_activity_spectate(secret) -> void:
	print(secret)
