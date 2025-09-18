namespace drawing {
	void render() {
		while (g_drawing->m_msg.message != WM_QUIT) {
			if (PeekMessageA(&g_drawing->m_msg, g_drawing->m_window_handle, 0, 0, PM_REMOVE)) {
				TranslateMessage(&g_drawing->m_msg);
				DispatchMessage(&g_drawing->m_msg);
			}

			if (GetAsyncKeyState(VK_INSERT) & 1)
				g_drawing->m_menu_active = !g_drawing->m_menu_active;

			g_drawing->update_affinity();
			g_drawing->new_frame();
			g_drawing->draw_menu();

			if (config::misc::enabled) {
			}

			g_drawing->draw_frame();
		}

		g_drawing->destroy();
	}
}