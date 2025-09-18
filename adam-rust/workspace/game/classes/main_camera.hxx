namespace classes {
	class c_main_camera {
	public:
		static c_main_camera* camera_instance() {
			std::uintptr_t camera = g_driver->read<std::uintptr_t>(g_driver->m_game_assembly + engine::offsets::main_camera);
			if (!camera) return 0;

			camera = g_driver->read<std::uintptr_t>(camera + 0xB8);
			if (!camera) return 0;

			camera = g_driver->read<std::uintptr_t>(camera + engine::offsets::camera_instance);
			if (!camera) return 0;

			camera = g_driver->read<std::uintptr_t>(camera + 0x10);
			if (!camera) return 0;

			return (c_main_camera*)camera;
		}

		bool view_matrix() {
			if (!this) return false;

			return g_driver->read_memory((std::uintptr_t)this + 0x30C, engine::m_view_matrix, sizeof(engine::m_view_matrix));
		}
	};
} classes::c_main_camera* camera_instance = nullptr;