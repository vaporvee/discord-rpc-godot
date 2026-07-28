extends Node

@onready var discord_rpc: Object = Engine.get_singleton("DiscordRPC")

func _ready() -> void:
	if GDExtensionManager.is_extension_loaded("res://addons/discord-rpc-gd/bin/discord-rpc-gd.gdextension"):
		set_activity()
		discord_rpc.connect("activity_join",_on_activity_join)
		discord_rpc.connect("activity_spectate",_on_activity_spectate)
		discord_rpc.connect("relationships_init",_on_relationship_init)
		discord_rpc.connect("updated_relationship", _on_updated_relationship)

func set_activity() -> void:
	discord_rpc.clear(false)
	discord_rpc.app_id = 1099618430065324082
	discord_rpc.details = "A demo activity by vaporvee#1231"
	discord_rpc.state = "Checkpoint 23/23"
	
	discord_rpc.large_image = "example_game"
	discord_rpc.large_image_text = "Try it now!"
	discord_rpc.small_image = "boss"
	discord_rpc.small_image_text = "Fighting the end boss! D:"
	discord_rpc.end_timestamp = int(Time.get_unix_time_from_system()) + 3600 # +1 hour in unix time
	
	# It is NOT recommended to manage secrets locally! It's meant to be a payload wich the server understands and 
	# returns the other variables like current_party_size, party_id etc. Most of the values must differ from the others.
	var my_secret: String = str(randi_range(0,999999))
	
	discord_rpc.party_id = "mylobbycanbeeverything_" + my_secret
	discord_rpc.current_party_size = 1
	discord_rpc.max_party_size = 4
	discord_rpc.match_secret = "m_" + my_secret #better use seeds with 1 to 1 range instead of just chars
	discord_rpc.join_secret = "j_" + my_secret
	discord_rpc.spectate_secret = "s_" + my_secret
	discord_rpc.is_public_party = true
	discord_rpc.instanced = true #required for spectate
	#discord_rpc.start_timestamp = int(Time.get_unix_time_from_system())
	discord_rpc.register_command("C:\\Users\\yanni\\Desktop\\demo\\DiscordRPC.exe")
	#discord_rpc.register_steam(1389990)
	discord_rpc.refresh()

var user_request: Dictionary;

func _on_activity_join_request(user_requesting: Dictionary) -> void:
	print(user_requesting)
	user_request = user_requesting

func _on_activity_join(secret: String) -> void:
	if(discord_rpc.join_secret != secret):
		discord_rpc.current_party_size = clamp(int(secret) + 1, 0, discord_rpc.max_party_size)
		discord_rpc.party_id = secret.replace("j_","mylobbycanbeeverything_")
		discord_rpc.match_secret = secret.replace("j_","m_")
		discord_rpc.join_secret = secret
		discord_rpc.spectate_secret = secret.replace("j_","s_")
		discord_rpc.refresh()

func _on_activity_spectate(secret: String) -> void:
	print(secret)

func _on_relationship_init() -> void:
	print("initialized")

func _on_updated_relationship(relationship: Dictionary) -> void:
	print(relationship)
