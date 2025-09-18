namespace classes {
	class c_player_model {
	public:
		engine::f_vector position() {
			engine::f_vector position = g_driver->read<engine::f_vector>((std::uintptr_t)this + engine::offsets::position);
			if (position.empty()) return engine::f_vector(); return position;
		}
	};
}