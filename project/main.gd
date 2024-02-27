extends Node

func _ready() -> void:
	set_activity()
	DiscordSDK.connect("activity_join_request",_on_activity_join_request)
	DiscordSDK.connect("activity_join",_on_activity_join)
	DiscordSDK.connect("activity_spectate",_on_activity_spectate)
	DiscordSDK.connect("relationships_init",_on_relationship_init)
	DiscordSDK.connect("updated_relationship", _on_updated_relationship)

func set_activity() -> void:
	DiscordSDK.clear(false)
	DiscordSDK.app_id = 1099618430065324082
	DiscordSDK.details = "A demo activity by vaporvee#1231"
	DiscordSDK.state = "Checkpoint 23/23"
	
	DiscordSDK.large_image = "example_game"
	DiscordSDK.large_image_text = "Try it now!"
	DiscordSDK.small_image = "boss"
	DiscordSDK.small_image_text = "Fighting the end boss! D:"
	DiscordSDK.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	# It is NOT recommended to manage secrets locally! It's meant to be a payload wich the server understands and 
	# returns the other variables like current_party_size, party_id etc. Most of the values must differ from the others.
	var my_secret: String = str(randi_range(0,999999))
	
	DiscordSDK.party_id = "mylobbycanbeeverything_" + my_secret
	DiscordSDK.current_party_size = 1
	DiscordSDK.max_party_size = 4
	DiscordSDK.match_secret = "m_" + my_secret #better use seeds with 1 to 1 range instead of just chars
	DiscordSDK.join_secret = "j_" + my_secret
	DiscordSDK.spectate_secret = "s_" + my_secret
	DiscordSDK.is_public_party = true
	DiscordSDK.instanced = true #required for spectate
	#DiscordSDK.start_timestamp = int(Time.get_unix_time_from_system())
	DiscordSDK.register_command("C:\\Users\\yanni\\Desktop\\demo\\DiscordSDK.exe")
	#DiscordSDK.register_steam(1389990)
	DiscordSDK.refresh()

var user_request: Dictionary;

func _on_activity_join_request(user_requesting) -> void:
	print(user_requesting)
	user_request = user_requesting

func _on_activity_join(secret) -> void:
	if(DiscordSDK.join_secret != secret):
		DiscordSDK.current_party_size = clamp(int(secret) + 1, 0, DiscordSDK.max_party_size)
		DiscordSDK.party_id = secret.replace("j_","mylobbycanbeeverything_")
		DiscordSDK.match_secret = secret.replace("j_","m_")
		DiscordSDK.join_secret = secret
		DiscordSDK.spectate_secret = secret.replace("j_","s_")
		DiscordSDK.refresh()

func _on_activity_spectate(secret) -> void:
	print(secret)

func _on_relationship_init():
	print("initialized")

func _on_updated_relationship(relationship):
	print(relationship)

