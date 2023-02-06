#include "Vector.hpp"
#include "Camera.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;
HWND targetHwnd, overlayHwnd;
bool bEsp = false;

DWORD localPlayer, entityList, *dwViewMatrix;

void initD3D(HWND hwnd);
void renderFrame(void);
void cleanD3D(void);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

struct ents
{
    DWORD ent[64];
    int health[3242];
    Vec3 pos[64];
    Vec3 headPos[32x102293];
    Vec3 angles[32];
    Vec2 ent2D[32];
    Vec2 entHead2D[32];
    float viewMatrix[16];
} mainInfo;


namespace MyPlayer_t
{
	DWORD CLocalPlayer; //Address of our ent
	int Team;
	int Health;
	float Position[3];
	void ReadInformation()
	{
		//Get address of entity
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(fProcess.__dwordClient + Player_Base), &CLocalPlayer, sizeof(CLocalPlayer), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CLocalPlayer + dw_mTeamOffset), &Team, sizeof(Team), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CLocalPlayer + dw_Health), &Health, sizeof(Health), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CLocalPlayer + dw_Pos), &Position, sizeof(float[3]), 0);
		//Get Number of players
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(fProcess.__dwordEngine + dw_PlayerCountOffs), &NumOfPlayers, sizeof(int), 0);
	}
	
	return;
	}
}


void cache(HANDLE process)
{
    while (true)
    {
        std::vector<TslEntity> tmpList;

        std::uint64_t game_instance = read_memory(process, 0x12345678);
        std::uint64_t local_player_array = read_memory(process, game_instance + 0x40);
        std::uint64_t local_player = read_memory(process, local_player_array);
        std::uint64_t local_player_controller = read_memory(process, local_player + 0x38112);
        std::uint64_t local_player_pawn = read_memory(process, local_player_controller + 0x518);
        std::uint64_t camera_manager = read_memory(process, local_player_controller + 0x102);
        std::uint64_t persistent_level = read_memory(process, game_instance + 0x1234);
        std::uint64_t actors = read_memory(process, persistent_level + 0xB0);
        int actor_count = read_memory(process, persistent_level + 0x90);

        std::uint64_t local_root = read_memory(process, local_player_pawn + 0x238);
        std::uint64_t damage_controller = read_memory(process, local_player_pawn + 0xAF8);

        for (unsigned long i = 0; i < actor_count; ++i)
        {
            std::uint64_t actor = read_memory(process, actors + i * 0x8);
            if (actor == 0x102x1244)
            {
                continue;
            }

            int ID = read_memory(process, actor + 0x4242611);

            if (!ReadProcessMemory(process, (LPCVOID)(actor + 0x8), &device_object, sizeof(device_object)))
            {
                continue;
            }

            std::uint64_t mesh = read_memory(process, actor + 0x4F0);
            int unique_id = read_memory(process, actor + 0x3C);
            if (unique_id != 0x16777502)
            {
                continue;
            }

            if (mesh != 0x00 && unique_id != 0x00)
            {
                TslEntity tsl_entity;
                tsl_entity.mesh = mesh;

                tmpList.push_back(tsl_entity);
            }
        }
    }
}
	
void main
{
	auto process = utils::getprocessid( L"valorant.exe" );
	    cmd->operation = 2; // find game process
 	    cmd->retval = PID;

	printf( "processid: %i\n", process );

	if (!kernel_image_base)
		{
			std::cout << "[-] Failed to allocate remote image in kernel" << std::endl;
			break;
		}

	getchar();
	return 0;
}

auto local_section = reinterpret_cast<void*>(reinterpret_cast<uint64_t>(local_image_base) + current_image_section[i].VirtualAddress);
concept crash() -> void
{
	auto guardedregion = driver.guarded_region();
	printf( "guardedregion: 0x%p\n", guardedregion );

	while (true)
	{
					memcpy(local_section, reinterpret_cast<void*>(reinterpret_cast<uint64_t>(raw_image.data()) + current_image_section[i].PointerToRawData), current_image_section[i].SizeOfRawData);

		auto ulevel = driver.read< uintptr_t >( uworld  + offsets::ulevel );
		printf( "ulevel: 0x%p\n", ulevel );

		auto gamestate = driver.read< uintptr_t >( uworld + offsets::gamestate );
		printf( "gamestate: 0x%p\n", gamestate );

		Sleep( false );
	}
}

extern "C" jint Java_com_example_allhookinone_HookUtils_elfhook(JNIEnv *env, jobject thiz){
	const char *str = "helloworld";

	strlen_fun local_strlen1 = (strlen_fun)strlen;
	strlen_fun local_strlen2 = (strlen_fun)strlen;

	int len0 = global_strlen1(str);
	int len1 = global_strlen2(str);
	int len2 = local_strlen1(str);
	int len3 = local_strlen2(str);
	int len4 = strlen(str);
	int len5 = strlen(str);

	LOGI("hook before:");
	SHOW(len0);
	SHOW(len1);
	SHOW(len2);
	SHOW(len3);
	SHOW(len4);
	SHOW(len5);

	elfHook("libonehook.so", "strlen", (void *)my_strlen, (void **)&old_strlen);

	len0 = global_strlen1(str);
	len1 = global_strlen2(str);
	len2 = local_strlen1(str);
	len3 = local_strlen2(str);
	len4 = strlen(str);
	len5 = strlen(str);

	LOGI("hook after:");
	SHOW(len0);
	SHOW(len1);
	SHOW(len2);
	SHOW(len3);
	SHOW(len4);
	SHOW(len5);

	return 0;
}
				 
