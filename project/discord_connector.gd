extends DiscordConnector

func _on_user_connected(access_token: String, refresh_token: String, expires_in: int) -> void:
	print_debug("Access token: %s \nRefresh Token: %s \nExpires in: %s" % [access_token, refresh_token, expires_in])

func _on_user_connection_failed(error: String) -> void:
	push_error("User connection failed! Error: " + error)

func _on_user_update_failed(error: String) -> void:
	push_error("User update failed! Error: " + error)

func _on_connection_ready() -> void:
	print_debug("CONNECTION READY")
	$DiscordLobby.create_or_join_lobby("beanis")

func _on_connection_error(error: String) -> void:
	push_error(error)
