extends Node

func _ready():
	DiscordSDK.set_app_id(918857075105349632)
	DiscordSDK.set_details("Made with GDExtension")
	DiscordSDK.set_state("This is a test from GDScript in Godot 4") #TODO:Change functions to variables if possible
	DiscordSDK.refresh_activity()
