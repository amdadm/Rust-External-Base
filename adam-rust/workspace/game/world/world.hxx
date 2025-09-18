namespace world {
	void loop_actors() {
		for (;;) {
			SleepEx(1200, false);
			classes::c_base_networkable* entity(classes::c_base_networkable::get_entity());
			if (!entity) { continue; }

			camera_instance = classes::c_main_camera::camera_instance();
			if (!camera_instance) { continue; }

			classes::c_base_networkable* entity_array = entity->entity_array();
			if (!entity_array) { continue; }

			local_player = entity_array->local_player();
			if (!local_player) { continue; }

			int32_t entity_count = entity->entity_count();
			if (entity_count < 0 || entity_count > 20000) { continue; }

			std::vector<classes::vector_push> entity_player_pool = { };
			for (int32_t i = 0; i < entity_count; i++) {
				classes::c_base_networkable* entity = 0;
				entity = entity_array->get_entity(i);
				if (!entity) { continue; }

				classes::c_base_networkable* entity_object = entity->entity_object();
				if (!entity_object) { continue; }

				classes::c_base_networkable* game_object = entity_object->game_object();
				if (!game_object) { continue; }

				std::string game_buffer = game_object->game_buffer();
				if (game_buffer.empty()) { continue; }

				if (config::visuals::scientist && (
					game_buffer.find(encrypt("assets/prefabs/npc/bandit")) != std::string::npos ||
					game_buffer.find(encrypt("tunneldweller")) != std::string::npos ||
					game_buffer.find(encrypt("npc_bandit_guard")) != std::string::npos ||
					game_buffer.find(encrypt("scientistnpc")) != std::string::npos)) {
					classes::c_base_player* player = entity_object->base_player();

					classes::base_player base_player;
					base_player.player = player;
					base_player.scientist = true;
					entity_player_pool.push_back({ base_player, classes::prefab_list(), true });
				}

				if (config::visuals::player && game_buffer.find(encrypt("player.prefab")) != std::string::npos) {
					classes::c_base_player* player = entity_object->base_player();

					classes::base_player base_player;
					base_player.player = player;
					base_player.scientist = false;
					entity_player_pool.push_back({ base_player, classes::prefab_list(), true });
				}
			}
			classes::entity_vector_pool.mutex.lock();
			classes::entity_vector_pool.vec = entity_player_pool;
			classes::entity_vector_pool.mutex.unlock();
		}
	}
}