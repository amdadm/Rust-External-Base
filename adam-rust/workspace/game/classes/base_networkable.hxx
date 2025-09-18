namespace classes {
	class c_base_networkable {
	public:
		static c_base_networkable* get_entity() {
			std::uintptr_t base_networkable = g_driver->read<std::uintptr_t>(g_driver->m_game_assembly + engine::offsets::base_networkable);
			//logging::print( encrypt( "base_networkable: %llx" ), base_networkable);
			if (!base_networkable) return 0;

			base_networkable = g_driver->read<std::uintptr_t>(base_networkable + 0xB8);
			//logging::print( encrypt( "base_networkable: %llx" ), base_networkable);
			if (!base_networkable) return 0;

			base_networkable = g_driver->read<std::uintptr_t>(base_networkable + engine::offsets::entities);
			//logging::print( encrypt( "base_networkable: %llx" ), base_networkable);
			if (!base_networkable) return 0;

			base_networkable = il2cpp::decrypt::entities(base_networkable);
			//logging::print( encrypt( "base_networkable: %llx" ), base_networkable);
			if (!base_networkable) return 0;

			base_networkable = g_driver->read<std::uintptr_t>(base_networkable + engine::offsets::entity_list);
			//logging::print( encrypt( "base_networkable: %llx" ), base_networkable);
			if (!base_networkable) return 0;

			base_networkable = il2cpp::decrypt::entity_list(base_networkable);
			//logging::print( encrypt( "base_networkable: %llx" ), base_networkable);
			if (!base_networkable) return 0;

			base_networkable = g_driver->read<std::uintptr_t>(base_networkable + engine::offsets::buffer);
			//logging::print( encrypt( "base_networkable: %llx" ), base_networkable);
			if (!base_networkable) return 0;

			return (c_base_networkable*)base_networkable;
		}

		std::int32_t entity_count() {
			int32_t count = g_driver->read<int32_t>((std::uintptr_t)this + engine::offsets::count);
			if (!count) return 0; return count;
		}

		c_base_networkable* entity_array() {
			std::uintptr_t array = g_driver->read<std::uintptr_t>((std::uintptr_t)this + engine::offsets::array);
			if (!array) return 0; return (c_base_networkable*)array;
		}

		c_base_networkable* get_entity(int i) {
			std::uintptr_t entity = g_driver->read<std::uintptr_t>((std::uintptr_t)this + 0x20 + (i * 0x08));
			if (!entity) return 0; return (c_base_networkable*)entity;
		}

		c_base_networkable* entity_object() {
			std::uintptr_t object = g_driver->read<std::uintptr_t>((std::uintptr_t)this + 0x10);
			if (!object) return 0; return (c_base_networkable*)object;
		}

		c_base_networkable* game_object() {
			std::uintptr_t object = g_driver->read<std::uintptr_t>((std::uintptr_t)this + 0x30);
			if (!object) return 0; return (c_base_networkable*)object;
		}

		std::string game_buffer() {
			std::uintptr_t buffer = g_driver->read<std::uintptr_t>((std::uintptr_t)this + 0x60);
			if (!buffer) return std::string(); return g_driver->read_string(buffer);
		}

		c_base_player* base_player() {
			std::uintptr_t player = g_driver->read<std::uintptr_t>((std::uintptr_t)this + 0x28);
			if (!player) return 0; return (c_base_player*)player;
		}

		c_base_player* local_player() {
			std::uintptr_t local = g_driver->read<std::uintptr_t>((std::uintptr_t)this + 0x20 + (0 * 0x8));
			if (!local) return 0; return (c_base_player*)local;
		}
	};
}