## This always needs to run in the background if you want to comunicate with the discord client.
extends Node

func _process(delta) -> void:
	discord_sdk.coreupdate()
