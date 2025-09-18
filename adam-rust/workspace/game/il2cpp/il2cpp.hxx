#pragma once
namespace il2cpp {
	std::uintptr_t il2cpp_get_handle(std::int32_t object_handle_id) {
		std::uintptr_t rdi_1 = object_handle_id >> 3;
		std::uintptr_t rcx_1 = (object_handle_id & 7) - 1;
		std::uintptr_t address = g_driver->m_game_assembly + engine::offsets::il2cpp_handle + rcx_1 * 0x28;
		std::uint32_t limit = g_driver->read<std::uint32_t>(address + 0x10);
		if (rdi_1 < limit) {
			std::uintptr_t obj_address = g_driver->read<std::uintptr_t>(address);
			std::uint32_t bit_mask = g_driver->read<std::uint32_t>(obj_address + ((rdi_1 >> 5) << 2));
			if (test_bitd(bit_mask, rdi_1 & 0x1f)) {
				std::uintptr_t obj_array = g_driver->read<std::uintptr_t>(address + 0x8) + (rdi_1 << 3);
				return g_driver->read<BYTE>(address + 0x14) > 1
					? g_driver->read<std::uintptr_t>(obj_array)
					: ~g_driver->read<std::uint32_t>(obj_array);
			}
		} return 0;
	}

	namespace decrypt {
		inline std::uintptr_t entities(std::uintptr_t a1) {
			__int64* v4; // rdx
			int v5; // r8d
			unsigned int v6; // ecx
			unsigned int v7; // eax
			__int64 v8; // rcx
			__int64 v24; // [rsp+20h] [rbp-28h] BYREF

			v4 = &v24;
			v24 = g_driver->read<std::uint64_t>(a1 + 0x18);
			v5 = 2;
			do {
				v6 = *(_DWORD*)v4;
				v7 = *(_DWORD*)v4;
				v4 = (__int64*)((char*)v4 + 4);
				*((_DWORD*)v4 - 1) = (((((v7 << 28) | (v6 >> 4)) - 161785282) << 21) | ((((v7 << 28) | (v6 >> 4)) - 161785282) >> 11)) ^ 0x88E819FB;
				--v5;
			} while (v5);
			v8 = v24; return il2cpp_get_handle(v24);
		}

		inline std::uintptr_t entity_list(std::uintptr_t a1) {
			uint64_t rax = g_driver->read<std::uint64_t>(a1 + 0x18);
			uint64_t* rdx = &rax;
			uint32_t r8d = 0x2;
			uint32_t eax, ecx;

			do {
				ecx = *(uint32_t*)(rdx);
				eax = *(uint32_t*)(rdx);
				rdx = (uint64_t*)((uint8_t*)rdx + 0x4);
				eax = eax << 0x1c;
				ecx = ecx >> 0x4;
				ecx = ecx | eax;
				ecx = ecx + 0xFFFFFFFFC2BEE621;
				eax = ecx;
				ecx = ecx << 0x1e;
				eax = eax >> 0x2;
				eax = eax | ecx;
				*((uint32_t*)rdx - 1) = eax;
				--r8d;
			} while (r8d);
			return il2cpp_get_handle(rax);
		}
	}
}