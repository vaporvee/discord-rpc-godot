extends Node

func _ready():
	DiscordSDK.app_id = 918857075105349632
	DiscordSDK.details = "Made with GDExtension"
	DiscordSDK.state = "This is a test from GDScript in Godot 4"
	
	DiscordSDK.refresh()
	$Info.text = $Info.text.replace("{id}",str(DiscordSDK.app_id)).replace("{details}",DiscordSDK.details).replace("{state}",DiscordSDK.state)
