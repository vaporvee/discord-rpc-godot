extends DiscordConnector

func _on_user_connected(access_token: String, refresh_token: String, expires_in: int) -> void:
	print_debug("Access token: %s \nRefresh Token: %s \nExpires in: %s" % [access_token, refresh_token, expires_in])

func _on_user_updated() -> void:
	print_debug("USER UPDATED")
	await get_tree().create_timer(2).timeout
	print("oop")
	$DiscordLobby.create_or_join_lobby("beanis")

func _on_user_connection_failed(error: String) -> void:
	push_error("User connection failed! Error: " + error)

func _on_user_update_failed(error: String) -> void:
	push_error("User update failed! Error: " + error)
