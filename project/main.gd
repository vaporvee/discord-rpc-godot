extends Node

func _ready():
	Discord_Activity.app_id = 918857075105349632
	Discord_Activity.details = "Made with GDExtension"
	Discord_Activity.state = "This is a test from GDScript in Godot 4"
	
	Discord_Activity.refresh()
	$Info.text = $Info.text.replace("{id}",str(Discord_Activity.app_id)).replace("{details}",Discord_Activity.details).replace("{state}",Discord_Activity.state)
