extends Node

func _ready():
	DiscordActivity.set_app_id(918857075105349632)
	DiscordActivity.set_details("Made with GDExtension")
	DiscordActivity.set_state("This is a test from GDScript in Godot 4") #TODO:Change functions to variables if possible
	DiscordActivity.refresh_activity()
