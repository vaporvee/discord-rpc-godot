extends Node

func _ready() -> void:
	set_activity()
	DiscordRPC.connect("activity_join_request",_on_activity_join_request)
	DiscordRPC.connect("activity_join",_on_activity_join)
	DiscordRPC.connect("activity_spectate",_on_activity_spectate)
	DiscordRPC.connect("relationships_init",_on_relationship_init)
	DiscordRPC.connect("updated_relationship", _on_updated_relationship)

func set_activity() -> void:
	DiscordRPC.clear(false)
	DiscordRPC.app_id = 1099618430065324082
	DiscordRPC.details = "A demo activity by vaporvee#1231"
	DiscordRPC.state = "Checkpoint 23/23"
	
	DiscordRPC.large_image = "example_game"
	DiscordRPC.large_image_text = "Try it now!"
	DiscordRPC.small_image = "boss"
	DiscordRPC.small_image_text = "Fighting the end boss! D:"
	DiscordRPC.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	# It is NOT recommended to manage secrets locally! It's meant to be a payload wich the server understands and 
	# returns the other variables like current_party_size, party_id etc. Most of the values must differ from the others.
	var my_secret: String = str(randi_range(0,999999))
	
	DiscordRPC.party_id = "mylobbycanbeeverything_" + my_secret
	DiscordRPC.current_party_size = 1
	DiscordRPC.max_party_size = 4
	DiscordRPC.match_secret = "m_" + my_secret #better use seeds with 1 to 1 range instead of just chars
	DiscordRPC.join_secret = "j_" + my_secret
	DiscordRPC.spectate_secret = "s_" + my_secret
	DiscordRPC.is_public_party = true
	DiscordRPC.instanced = true #required for spectate
	#DiscordRPC.start_timestamp = int(Time.get_unix_time_from_system())
	DiscordRPC.register_command("C:\\Users\\yanni\\Desktop\\demo\\DiscordRPC.exe")
	#DiscordRPC.register_steam(1389990)
	DiscordRPC.refresh()

var user_request: Dictionary;

func _on_activity_join_request(user_requesting) -> void:
	print(user_requesting)
	user_request = user_requesting

func _on_activity_join(secret) -> void:
	if(DiscordRPC.join_secret != secret):
		DiscordRPC.current_party_size = clamp(int(secret) + 1, 0, DiscordRPC.max_party_size)
		DiscordRPC.party_id = secret.replace("j_","mylobbycanbeeverything_")
		DiscordRPC.match_secret = secret.replace("j_","m_")
		DiscordRPC.join_secret = secret
		DiscordRPC.spectate_secret = secret.replace("j_","s_")
		DiscordRPC.refresh()

func _on_activity_spectate(secret) -> void:
	print(secret)

func _on_relationship_init():
	print("initialized")

func _on_updated_relationship(relationship):
	print(relationship)

