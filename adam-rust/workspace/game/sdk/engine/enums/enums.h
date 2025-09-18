namespace engine {

    // base_player_class

    enum class e_camera_mode : uint8_t {
        first_person = 0,
        third_person = 1,
        eyes = 2,
        first_person_with_arms = 3,
        DeathCamClassic = 4,
        last = 3
    };

    enum class e_map_note_type : uint8_t {
        death = 0,
        point_of_interest = 1
    };

    enum class e_ping_type : uint8_t {
        hostile = 0,
        GoTo = 1,
        dollar = 2,
        loot = 3,
        node = 4,
        gun = 5,
        build = 6,
        last = 6
    };

    enum class e_player_flags : uint8_t {
        unused_1 = 1,
        unused_2 = 2,
        is_admin = 4,
        receiving_snapshot = 8,
        sleeping = 16,
        spectating = 32,
        wounded = 64,
        is_developer = 128,
        connected = 256,
        third_person_viewmode = 1024,
        eyes_viewmode = 2048,
        chat_mute = 4096,
        no_sprint = 8192,
        aiming = 16384,
        display_sash = 32768,
        relaxed = 65536,
        safe_zone = 131072,
        server_fall = 262144,
        incapacitated = 524288,
        workbench_1 = 1048576,
        workbench_2 = 2097152,
        workbench_3 = 4194304,
        voice_range_boost = 8388608,
        modify_clan = 16777216,
        loading_after_transfer = 33554432,
        no_respawn_zone = 67108864,
        is_in_tutorial = 134217728,
        is_restrained = 268435456,
        creative_mode = 536870912,
        waiting_for_gesture_interaction = 1073741824,
        ragdolling = -2147483648
    };

    enum class e_rps_win_state : uint8_t {
        win = 0,
        loss = 1,
        draw = 2
    };

    enum class e_time_category : uint8_t {
        wilderness = 1,
        monument = 2,
        base = 4,
        flying = 8,
        boating = 16,
        swimming = 32,
        driving = 64
    };

    enum class e_tutorial_item_allowance : uint8_t {
        always_allowed = -1,
        none = 0,
        level_1_hatchet_pickaxe = 10,
        level_2_planner = 20,
        level_3_bag_tc_door = 30,
        level_3_hammer = 35,
        level_4_spear_fire = 40,
        level_5_prepare_for_combat = 50,
        level_6_furnace = 60,
        level_7_workbench = 70,
        level_8_kayak = 80
    };

    // player_inventory_class

    enum class e_inventory_type : uint8_t {
        main = 0,
        belt = 1,
        wear = 2,
        backpack_contents = 3
    };

    // player_model_class

    enum class e_mount_poses : uint8_t {
        chair = 0,
        driving = 1,
        horseback = 2,
        heli_unarmed = 3,
        heli_armed = 4,
        hand_motor_boat = 5,
        motor_boat_passenger = 6,
        sit_generic = 7,
        sit_raft = 8,
        stand_drive = 9,
        sit_shooting_generic = 10,
        sit_minicopter_pilot = 11,
        sit_minicopter_passenger = 12,
        arcade_left = 13,
        arcade_right = 14,
        sit_summer_ring = 15,
        sit_summer_boogie_board = 16,
        sit_car_passenger = 17,
        sit_summer_chair = 18,
        sit_raft_no_paddle = 19,
        sit_secret_lab = 20,
        sit_workcart = 21,
        sit_cardgame = 22,
        sit_crane = 23,
        sit_snowmobile_shooting = 24,
        sit_retro_snowmobile_shooting = 25,
        driving_snowmobile = 26,
        zipline_hold = 27,
        sit_locomotive = 28,
        sit_throne = 29,
        parachute = 30,
        sit_dpv = 31,
        standing_ballista = 32,
        sit_battering_ram = 33,
        vine_swinging = 34,
        sit_ejectorseat = 35,
        sit_beanbag = 36,
        standing = 128
    };

    enum class e_reaction_dir : uint8_t {
        north = 0,
        south = 1,
        east = 2,
        west = 3
    };

    enum class e_swap_type : uint8_t {
        deploy = 0,
        turn_on = 1,
        turn_off = 2
    };

    // base_view_model_class

    enum class e_view_model_type : uint8_t {
        regular = 0,
        gesture = 1,
        shield = 2
    };
}