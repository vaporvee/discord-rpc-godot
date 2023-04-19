extends Node


# Called when the node enters the scene tree for the first time.
func _ready():
	DiscordSDK.debug()

func _process(_delta):
	DiscordSDK.updatedebug()
