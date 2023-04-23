extends Node

func _ready():
	#Discord_Activity.debug()
	Discord_Activity.app_id = 1099618430065324082
	Discord_Activity.details = "A demo activity by vaporvee#1231"
	Discord_Activity.state = "Checkpoint 23/23"
	
	Discord_Activity.large_image = "game"
	Discord_Activity.large_image_text = "Try it now!"
	Discord_Activity.small_image = "boss"
	Discord_Activity.small_image_text = "Fighting the end boss! D:"
	
	Discord_Activity.start_timestamp = int(Time.get_unix_time_from_system())
	#Discord_Activity.end_timestamp = 2492978400 #31. 12. 2048 in unix time

	Discord_Activity.refresh()
	$Info.text = $Info.text.replace("{id}",str(Discord_Activity.app_id)).replace("{details}",Discord_Activity.details).replace("{state}",Discord_Activity.state).replace("{lkey}",Discord_Activity.large_image).replace("{ltext}",Discord_Activity.large_image_text).replace("{skey}",Discord_Activity.small_image).replace("{stext}",Discord_Activity.small_image_text).replace("{stimestamp}",str(Discord_Activity.start_timestamp)).replace("{etimestamp}",str(Discord_Activity.end_timestamp))
