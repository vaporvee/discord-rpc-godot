extends Node

func _ready():
	DiscordSDK.app_id = 918857075105349632
	print(DiscordSDK.app_id)
	DiscordSDK.details = "Made with GDExtension"
	print(DiscordSDK.details)
	DiscordSDK.state = "This is a test from GDScript in Godot 4" #TODO:Change functions to variables if possible
	print(DiscordSDK.state)
	DiscordSDK.refresh()
