#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#include <chrono>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <winternl.h>
#include <cstdint>
#include <DbgHelp.h>
#include <thread>
#include <mutex>
#include <map>
#include <algorithm>
#include <d3d11.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <functional>
#include <cassert>
#include <corecrt_math.h>
#include <limits>
#include <numbers>
#include <shared_mutex>
#include <D3DX11.h>
#include <D3DX11core.h>
#include <D3DX11tex.h>
#include <dwmapi.h>
#include <unordered_set>
#include <filesystem>
#include <shellapi.h>
#include <emmintrin.h>
#include <atomic>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "ntdll.lib")

#ifdef _MSC_VER
#include <intrin.h>
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE __attribute__((always_inline)) inline
#endif

#include <dependencies/font/font.h>
#include <dependencies/imgui/imgui.h>
#include <dependencies/imgui/imgui_impl_dx11.h>
#include <dependencies/imgui/imgui_impl_win32.h>

#include <workspace/config/config.h>

#include <dependencies/hexrays/hexrays.h>
#include <dependencies/skcrypt/skcrypter.h>
#include <dependencies/lazy/lazy_importer.h>
#include <dependencies/logger/logger.hxx>

#include <impl/libcrypt/libcrypt.hxx>
auto g_lib = std::make_shared< lib::c_libcrypt >();
#include <impl/exception/exception.hxx>

#include <impl/wdk/wdk.h>

#include <workspace/driver/driver.hxx>
auto g_driver = std::make_shared< driver::c_driver >();

#include <workspace/game/sdk/engine/enums/enums.h>

#include <workspace/game/sdk/math/math.hxx>

#include <workspace/game/sdk/engine/structs/structs.h>

#include <workspace/game/sdk/sdk.h>

#define test_bitd(value, bit) (((value) & (1 << (bit))) != 0)
#include <workspace/game/il2cpp/il2cpp.hxx>

#include <workspace/game/classes/player_model.hxx>
#include <workspace/game/classes/base_player.hxx>
#include <workspace/game/classes/base_networkable.hxx>
#include <workspace/game/classes/main_camera.hxx>

#include <workspace/drawing/drawing.hxx>
auto g_drawing = std::make_shared< drawing::c_drawing >();

#include <workspace/game/world/world.hxx>

#include <workspace/drawing/render/render.hxx>