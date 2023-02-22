#include "Settings.h"
#include "Menu.h"
#include <iostream>
#include "Globals.h"

namespace my_game {
    extern byte game_data[];

    #pragma pack(push, 1)
    struct ArrayHeader {
        uint64_t ptr;
        uint32_t size;
        uint64_t kernel_read;
    };

    struct AimbotSetup {
        uint32_t hotkey;
        // Add other aimbot setup data here
    };

    struct Camera {
        Vector3 position;
        Vector3 rotation;
        float fov;
    };

    struct ControlRotation {
        Vector3 ctrl_rotation;
        Vector3 write_ctrl_rotation;
        bool write_flag;
    };

    struct GameData {
        ArrayHeader actors;
        uint64_t player_state;
        Camera camera;
        ControlRotation control_rotation;
        uintptr_t local_pawn;
        // Add other game data here
    };

    struct Aimbot {
        AimbotSetup setup;
        // Add other aimbot data here
    };

    struct MyGame {
        GameData data;
        Aimbot aimbot;
        // Add other game-related data here
    };
}
	
#pragma pack(pop)
#endif // !MAGIC_STRUCTS

	extern bool magic_scan(uintptr_t& worldcrypt_key, uintptr_t& worldcrypt_state);
	extern bool write_shell(uint64_t decrypted_world, uint64_t base, uintptr_t& pentitycache, uintptr_t& plocalproxy);
	extern HijackState read_results();
	static (processid) 
}
