extends Node

func _ready():
	DiscordSDK.app_id = 918857075105349632
	DiscordSDK.details = "Made with GDExtension"
	DiscordSDK.state = "This is a test from GDScript in Godot 4"

	DiscordSDK.refresh()
