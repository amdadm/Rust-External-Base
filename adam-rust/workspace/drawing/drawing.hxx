ImFont* roboto_font_small;
namespace drawing {
    struct find_window_data {
        unsigned long pid;
        std::string class_name;
        std::string window_name;
        HWND hwnd;
    };

    BOOL __stdcall enum_windows_proc(HWND hwnd, LPARAM l_param) {
        find_window_data* data = (find_window_data*)l_param;

        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);

        if (pid == data->pid) {
            char class_name[256];
            GetClassNameA(hwnd, class_name, sizeof(class_name));
            if (data->class_name == class_name) {
                char window_name[256];
                GetWindowTextA(hwnd, window_name, sizeof(window_name));
                if (data->window_name == window_name) {
                    data->hwnd = hwnd;
                    return false;
                }
            }
        }
        return true;
    }

    HWND find_child_window_from_parent(HWND parent, const char* class_name, const char* window_name) {
        DWORD pid = 0;
        GetWindowThreadProcessId(parent, &pid);

        if (pid == 0)
            return nullptr;

        find_window_data data = { pid, class_name, window_name, nullptr };
        EnumWindows(enum_windows_proc, reinterpret_cast<LPARAM>(&data));
        return data.hwnd;
    }

    class c_drawing {
    public:
        bool hijack() {
            m_width = GetSystemMetrics(SM_CXSCREEN);
            m_height = GetSystemMetrics(SM_CYSCREEN);

            m_width_center = m_width / 2;
            m_height_center = m_height / 2;

            HWND game_hwnd = FindWindowA(("UnityWndClass"), ("Rust"));

            m_window_handle = find_child_window_from_parent(game_hwnd, "IME", "Default IME");
            if (!m_window_handle) return false;

            RECT rect = get_client_area_and_size(game_hwnd);
            if (!SetWindowPos(m_window_handle, nullptr, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER))
                return false;

            GetWindowRect(GetDesktopWindow(), &rect);
            SetWindowLong(m_window_handle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

            MARGINS window_margin{ -1 };
            DwmExtendFrameIntoClientArea(m_window_handle, &window_margin);
            SetLayeredWindowAttributes(m_window_handle, 0, 255, LWA_ALPHA);

            UpdateWindow(m_window_handle);
            ShowWindow(m_window_handle, SW_SHOW);
            return true;
        }

        RECT get_client_area_and_size(HWND hwnd) {
            RECT rect;
            if (GetClientRect(hwnd, &rect)) {
                POINT top_left = { rect.left, rect.top };
                POINT bottom_right = { rect.right, rect.bottom };

                ClientToScreen(hwnd, &top_left);
                ClientToScreen(hwnd, &bottom_right);

                rect.left = top_left.x;
                rect.top = top_left.y;
                rect.right = bottom_right.x;
                rect.bottom = bottom_right.y;
            }
            else {
                rect = { 0, 0, 0, 0 };
            }

            return rect;
        }

        bool setup() {
            DXGI_SWAP_CHAIN_DESC sd;
            ZeroMemory(&sd, sizeof(sd));
            sd.BufferCount = 2;
            sd.BufferDesc.Width = 0;
            sd.BufferDesc.Height = 0;
            sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            sd.BufferDesc.RefreshRate.Numerator = 60;
            sd.BufferDesc.RefreshRate.Denominator = 1;
            sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
            sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            sd.OutputWindow = m_window_handle;
            sd.SampleDesc.Count = 1;
            sd.SampleDesc.Quality = 0;
            sd.Windowed = TRUE;
            sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            D3D_FEATURE_LEVEL feature_level;
            const D3D_FEATURE_LEVEL feature_levels[2] = {
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_0
            };

            if (FAILED(D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                0,
                feature_levels,
                2,
                D3D11_SDK_VERSION,
                &sd,
                &m_swap_chain,
                &m_d3d_device,
                &feature_level,
                &m_device_context))) {
                return false;
            }

            create_render_target();
            setup_imgui();
            return true;
        }

        void create_render_target() {
            ID3D11Texture2D* back_buffer;
            m_swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
            if (back_buffer) {
                m_d3d_device->CreateRenderTargetView(back_buffer, nullptr, &m_render_target);
                back_buffer->Release();
            }
        }

        void setup_imgui() {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            ImGuiStyle& s = ImGui::GetStyle();

            auto font_size = 15.0;
            ImFontConfig font_cfg;
            font_cfg.OversampleH = 1;
            font_cfg.OversampleV = 1;
            font_cfg.PixelSnapH = true;

            io.Fonts->AddFontFromMemoryTTF(&roboto_ttf, sizeof roboto_ttf, 16, NULL, io.Fonts->GetGlyphRangesCyrillic());

            roboto_font_small = io.Fonts->AddFontFromMemoryTTF(&roboto_ttf, sizeof roboto_ttf, 15, NULL, io.Fonts->GetGlyphRangesCyrillic());

            D3DX11_IMAGE_LOAD_INFO iInfo;
            ID3DX11ThreadPump* threadPump{ nullptr };

            ImGui::StyleColorsDark();
            //s.FramePadding = ImVec2(10, 10);
            s.ItemSpacing = ImVec2(10, 10);
            s.FrameRounding = 1.f;
            s.WindowRounding = 1.f;
            s.WindowBorderSize = 0.f;
            s.PopupBorderSize = 0.f;
            s.WindowPadding = ImVec2(0, 0);
            s.ChildBorderSize = 1.f;
            s.Colors[ImGuiCol_Border] = ImVec4(0.f, 0.f, 0.f, 0.f);
            s.PopupRounding = 1.f;
            s.ScrollbarSize = 1;
            s.PopupBorderSize = 1.3f;

            ImGui_ImplWin32_Init(m_window_handle);
            ImGui_ImplDX11_Init(m_d3d_device, m_device_context);
        }

        void draw_menu() {
            if (!m_menu_active)
                return;

            ImGui::SetNextWindowSize(ImVec2(470, 340));
            ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            {
                ImGui::SetCursorPos(ImVec2(10, 30));
                ImGui::Checkbox("Player", &config::visuals::player);
                ImGui::SetCursorPos(ImVec2(10, 60));
                ImGui::Checkbox("Skeleton", &config::visuals::skeleton);
                ImGui::SetCursorPos(ImVec2(10, 90));
                ImGui::Checkbox("Name", &config::visuals::player_name);
            }
            ImGui::End();
        }

        void new_frame() {
            ImGui_ImplDX11_NewFrame();
            POINT p;
            GetCursorPos(&p);
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = ImVec2(p.x, p.y);
            io.MouseDown[0] = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
            io.MouseDown[1] = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        void draw_frame() {
            ImGui::Render();
            const float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            m_device_context->OMSetRenderTargets(1, &m_render_target, nullptr);
            m_device_context->ClearRenderTargetView(m_render_target, clear_color);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            m_swap_chain->Present(config::misc::vsync, 0);
        }

        bool is_window_focused() {
            if (g_driver->m_window_handle == GetForegroundWindow()) {
                return true;
            }

            if (g_driver->m_window_handle == GetActiveWindow()) {
                return true;
            }

            if (GetActiveWindow() == GetForegroundWindow()) {
                return true;
            }

            return false;
        }

        void destroy() {
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            if (m_render_target) { m_render_target->Release(); m_render_target = nullptr; }
            if (m_swap_chain) { m_swap_chain->Release(); m_swap_chain = nullptr; }
            if (m_device_context) { m_device_context->Release(); m_device_context = nullptr; }
            if (m_d3d_device) { m_d3d_device->Release(); m_d3d_device = nullptr; }
        }

        void update_affinity() const {
            DWORD window_affinity;
            if (GetWindowDisplayAffinity(m_window_handle, &window_affinity)) {
                auto new_affinity = config::misc::stream_proof ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE;
                if (window_affinity != new_affinity) {
                    SetWindowDisplayAffinity(m_window_handle, new_affinity);
                }
            }
        }

        int m_width = 0;
        int m_height = 0;

        int m_width_center = 0;
        int m_height_center = 0;

        MSG m_msg{ nullptr };
        HWND m_window_handle{ nullptr };

        bool m_menu_active = true;

    private:
        ID3D11Device* m_d3d_device = nullptr;
        ID3D11DeviceContext* m_device_context = nullptr;
        IDXGISwapChain* m_swap_chain = nullptr;
        ID3D11RenderTargetView* m_render_target = nullptr;
    };
}
