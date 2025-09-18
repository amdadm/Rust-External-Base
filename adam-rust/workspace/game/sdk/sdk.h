namespace engine {
    namespace offsets {
        std::uint32_t null = 0x0;
        std::uint32_t il2cpp_handle = 0xd554a60;

        std::uint32_t main_camera = 0xd1db760;
        std::uint32_t camera_instance = 0x58;

        std::uint32_t base_networkable = 0xd1fd838;
        std::uint32_t entities = 0x20;
        std::uint32_t entity_list = 0x10;
        std::uint32_t buffer = 0x20;
        std::uint32_t count = 0x18;
        std::uint32_t array = 0x10;

        std::uint32_t model = 0xc8;
        std::uint32_t bone_transform = 0x50;

        std::uint32_t player_flags = 0x588;
        std::uint32_t player_model = 0x598;
        std::uint32_t display_name = 0x358;
        std::uint32_t position = 0x1E8;
    }

    enum e_bone {
        pelvis = 0,
        l_hip = 1,
        l_knee = 2,
        l_foot = 3,
        l_toe = 4,
        l_ankle_scale = 5,
        penis = 6,
        GenitalCensor = 7,
        GenitalCensor_LOD0 = 8,
        Inner_LOD0 = 9,
        GenitalCensor_LOD1 = 11,
        GenitalCensor_LOD2 = 12,
        r_hip = 13,
        r_knee = 14,
        r_foot = 15,
        r_toe = 16,
        r_ankle_scale = 17,
        spine1 = 18,
        spine1_scale = 19,
        spine2 = 20,
        spine3 = 21,
        spine4 = 22,
        l_clavicle = 23,
        l_upperarm = 24,
        l_forearm = 25,
        l_hand = 26,
        l_index1 = 27,
        l_index2 = 28,
        l_index3 = 29,
        l_little1 = 30,
        l_little2 = 31,
        l_little3 = 32,
        l_middle1 = 33,
        l_middle2 = 34,
        l_middle3 = 35,
        l_prop = 36,
        l_ring1 = 37,
        l_ring2 = 38,
        l_ring3 = 39,
        l_thumb1 = 40,
        l_thumb2 = 41,
        l_thumb3 = 42,
        IKtarget_righthand_min = 43,
        IKtarget_righthand_max = 44,
        l_ulna = 45,
        neck = 46,
        head = 47,
        jaw = 48,
        eyeTranform = 49,
        l_eye = 50,
        l_Eyelid = 51,
        r_eye = 52,
        r_Eyelid = 53,
        r_clavicle = 54,
        r_upperarm = 55,
        r_forearm = 56,
        r_hand = 57,
        r_index1 = 58,
        r_index2 = 59,
        r_index3 = 60,
        r_little1 = 61,
        r_little2 = 62,
        r_little3 = 63,
        r_middle2 = 65,
        r_middle3 = 66,
        r_prop = 67,
        r_ring1 = 68,
        r_ring2 = 69,
        r_ring3 = 70,
        r_thumb1 = 71,
        r_thumb2 = 72,
        r_thumb3 = 73,
        IKtarget_lefthand_min = 74,
        IKtarget_lefthand_max = 75,
        r_ulna = 76,
        l_breast = 77,
        r_breast = 78,
        BoobCensor = 79,
        BreastCensor_LOD0 = 80,
        BreastCensor_LOD1 = 83,
        BreastCensor_LOD2 = 84
    };

    const std::vector<std::pair<int, int>> skeleton_pairs{
        {e_bone::neck, e_bone::r_upperarm},
        {e_bone::neck, e_bone::l_upperarm},
        {e_bone::l_upperarm, e_bone::l_forearm},
        {e_bone::l_forearm, e_bone::l_hand},
        {e_bone::r_upperarm, e_bone::r_forearm},
        {e_bone::r_forearm, e_bone::r_hand},
        {e_bone::neck, e_bone::pelvis},
        {e_bone::pelvis, e_bone::r_hip},
        {e_bone::pelvis, e_bone::l_hip},
        {e_bone::r_hip, e_bone::r_knee},
        {e_bone::r_knee, e_bone::r_foot},
        {e_bone::l_hip, e_bone::l_knee},
        {e_bone::l_knee, e_bone::l_foot}
    };

    struct transform_access_read_only {
        std::uintptr_t	TransformData;
        int			Index;
    };

    struct transform_data {
        std::uintptr_t TransformArray;
        std::uintptr_t TransformIndices;
    };

    engine::f_vector get_transform_position(std::uintptr_t transform) {
        std::uintptr_t transform_internal = g_driver->read<std::uintptr_t>(transform + 0x10);

        if (!transform_internal)
            return engine::f_vector();
        try
        {
            __m128 result;

            const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
            const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
            const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

            transform_access_read_only pTransformAccessReadOnly = g_driver->read<transform_access_read_only>(transform_internal + 0x38);
            transform_data transformData = g_driver->read<transform_data>(pTransformAccessReadOnly.TransformData + 0x18);

            if (!transformData.TransformArray)
                return engine::f_vector();

            if (!transformData.TransformIndices)
                return engine::f_vector();

            size_t sizeMatriciesBuf = sizeof(matrix_3x4) * pTransformAccessReadOnly.Index + sizeof(matrix_3x4);
            size_t sizeIndicesBuf = sizeof(int) * pTransformAccessReadOnly.Index + sizeof(int);

            void* pMatriciesBuf = malloc(sizeMatriciesBuf);
            void* pIndicesBuf = malloc(sizeIndicesBuf);

            if (pMatriciesBuf && pIndicesBuf)
            {
                if (transformData.TransformArray == 0 || transformData.TransformIndices == 0)
                    return engine::f_vector();

                // Read Matricies array into the buffer
                g_driver->read_memory(transformData.TransformArray, pMatriciesBuf, sizeMatriciesBuf);
                // Read Indices array into the buffer
                g_driver->read_memory(transformData.TransformIndices, pIndicesBuf, sizeIndicesBuf);

                __m128 Result = *reinterpret_cast<__m128*>(reinterpret_cast<std::uintptr_t>(pMatriciesBuf) + (0x30 * pTransformAccessReadOnly.Index));
                int TransformIndex = *reinterpret_cast<int*>((reinterpret_cast<std::uintptr_t>(pIndicesBuf) + (0x4 * pTransformAccessReadOnly.Index)));

                while (TransformIndex >= 0 && TransformIndex < (sizeMatriciesBuf / 0x30))
                {
                    if (!pMatriciesBuf || !pIndicesBuf || !&result || !&TransformIndex)
                        return engine::f_vector();

                    matrix_3x4 Matrix = *reinterpret_cast<matrix_3x4*>(reinterpret_cast<std::uintptr_t>(pMatriciesBuf) + (0x30 * TransformIndex));

                    if (!&Matrix)
                        return engine::f_vector();

                    __m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>(&Matrix._21), 0x00));	// xxxx
                    __m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>(&Matrix._21), 0x55));	// yyyy
                    __m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>(&Matrix._21), 0x8E));	// zwxy
                    __m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>(&Matrix._21), 0xDB));	// wzyw
                    __m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>(&Matrix._21), 0xAA));	// zzzz
                    __m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>(&Matrix._21), 0x71));	// yxwy
                    __m128 tmp7 = _mm_mul_ps(*reinterpret_cast<__m128*>(&Matrix._31), Result);

                    Result = _mm_add_ps(
                        _mm_add_ps(
                            _mm_add_ps(
                                _mm_mul_ps(
                                    _mm_sub_ps(
                                        _mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
                                        _mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
                                    _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
                                _mm_mul_ps(
                                    _mm_sub_ps(
                                        _mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
                                        _mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
                                    _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
                            _mm_add_ps(
                                _mm_mul_ps(
                                    _mm_sub_ps(
                                        _mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
                                        _mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
                                    _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
                                tmp7)), *(__m128*)(&Matrix._11));

                    TransformIndex = *reinterpret_cast<int*>(reinterpret_cast<std::uintptr_t>(pIndicesBuf) + (0x4 * TransformIndex));
                }

                free(pMatriciesBuf);
                free(pIndicesBuf);

                return engine::f_vector{ Result.m128_f32[0], Result.m128_f32[1], Result.m128_f32[2] };
            }

            return {};
        }
        catch (...) {
            return engine::f_vector();
        }
    }

    struct unity_string {
        char pad[0x10];
        int lenght;
        wchar_t buffer[128 + 1];
    };
}