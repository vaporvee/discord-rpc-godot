extends Node

func _ready() -> void:
	if GDExtensionManager.is_extension_loaded("res://addons/discord-rpc-gd/bin/discord-rpc-gd.gdextension"):
		set_activity()
		DiscordUtil.connect("activity_join_request",_on_activity_join_request)
		#DiscordUtil.connect("activity_join",_on_activity_join)
		DiscordUtil.connect("activity_spectate",_on_activity_spectate)
		DiscordUtil.connect("relationships_init",_on_relationship_init)
		DiscordUtil.connect("updated_relationship", _on_updated_relationship)

func set_activity() -> void:
	#DiscordUtil.clear(false)
	DiscordUtil.app_id = 1099618430065324082
	DiscordUtil.debug()
	#DiscordUtil.details = "A demo activity by vaporvee#1231"
	#DiscordUtil.state = "Checkpoint 23/23"
	#
	#DiscordUtil.large_image = "example_game"
	#DiscordUtil.large_image_text = "Try it now!"
	#DiscordUtil.small_image = "boss"
	#DiscordUtil.small_image_text = "Fighting the end boss! D:"
	#DiscordUtil.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	# It is NOT recommended to manage secrets locally! It's meant to be a payload wich the server understands and 
	# returns the other variables like current_party_size, party_id etc. Most of the values must differ from the others.
	#var my_secret: String = str(randi_range(0,999999))
	
	#DiscordUtil.party_id = "mylobbycanbeeverything_" + my_secret
	#DiscordUtil.current_party_size = 1
	#DiscordUtil.max_party_size = 4
	#DiscordUtil.match_secret = "m_" + my_secret #better use seeds with 1 to 1 range instead of just chars
	#DiscordUtil.join_secret = "j_" + my_secret
	#DiscordUtil.spectate_secret = "s_" + my_secret
	#DiscordUtil.is_public_party = true
	#DiscordUtil.instanced = true #required for spectate
	#DiscordUtil.start_timestamp = int(Time.get_unix_time_from_system())
	DiscordUtil.register_command("C:\\Users\\yanni\\Desktop\\demo\\DiscordUtil.exe")
	#DiscordUtil.register_steam(1389990)
	DiscordUtil.refresh()

var user_request: Dictionary;

func _on_activity_join_request(user_requesting: Dictionary) -> void:
	print(user_requesting)
	user_request = user_requesting

#func _on_activity_join(secret: String) -> void:
	#if(DiscordUtil.join_secret != secret):
		#DiscordUtil.current_party_size = clamp(int(secret) + 1, 0, DiscordUtil.max_party_size)
		#DiscordUtil.party_id = secret.replace("j_","mylobbycanbeeverything_")
		#DiscordUtil.match_secret = secret.replace("j_","m_")
		#DiscordUtil.join_secret = secret
		#DiscordUtil.spectate_secret = secret.replace("j_","s_")
		#DiscordUtil.refresh()

func _on_activity_spectate(secret: String) -> void:
	print(secret)

func _on_relationship_init() -> void:
	print("initialized")

func _on_updated_relationship(relationship: Dictionary) -> void:
	print(relationship)
