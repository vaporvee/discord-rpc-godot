## This is a Debug Node wich will show (only if the project runs) some usefull info and buttons/input
extends Node

func _ready() -> void:
	const DebugNodeGroup: PackedScene = preload("res://addons/discord-sdk-gd/nodes/Debug.tscn")
	add_child(DebugNodeGroup.instantiate())
