namespace classes {
	class c_base_player {
	public:
		c_player_model* player_model() {
			std::uintptr_t model = g_driver->read<std::uintptr_t>((std::uintptr_t)this + engine::offsets::player_model);
			if (!model) return 0; return (c_player_model*)model;
		}

		bool sleeping() {
			int flag = g_driver->read<int>((std::uintptr_t)(std::uintptr_t)this + engine::offsets::player_flags);
			if (!flag) return false; return (flag & static_cast<int>(engine::e_player_flags::sleeping)) != 0;
		}

		bool wounded() {
			int flag = g_driver->read<int>((std::uintptr_t)(std::uintptr_t)this + engine::offsets::player_flags);
			if (!flag) return false; return (flag & static_cast<int>(engine::e_player_flags::wounded)) != 0;
		}

		bool dead() {
			bool dead = g_driver->read<bool>((std::uintptr_t)this + engine::offsets::player_flags);
			return dead;
		}

		engine::f_vector get_bone_location(int i) {
			std::uintptr_t model = g_driver->read<std::uintptr_t>((std::uintptr_t)this + engine::offsets::model);
			if (!model) return engine::f_vector();

			std::uintptr_t bone_transform = g_driver->read<std::uintptr_t>(model + engine::offsets::bone_transform);
			if (!bone_transform) return engine::f_vector();

			std::uintptr_t value = g_driver->read<std::uintptr_t>((bone_transform + (0x20 + (i * 0x8))));
			if (!value) return engine::f_vector();

			return engine::get_transform_position(value);
		}
	};

	struct base_player {
		c_base_player* player;
		bool scientist;
	};

	struct prefab_list {
		std::string prefab_name;
		std::uintptr_t pos_ago;
	};

	struct vector_push {
		base_player player;
		prefab_list prefab;
		bool booler;
	}; engine::thread_rec<vector_push> entity_vector_pool = {};
} classes::c_base_player* local_player = nullptr;