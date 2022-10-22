#include "Vector.hpp"
#include "Camera.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

LPDIRECT3D9			d3d;
LPDIRECT3DDEVICE9	d3ddev;

HANDLE pHandle;
HWND targetHwnd, overlayHwnd;
Vec2 vecScreen;
int windowWidth, windowHeight, windowX, windowY;
bool bMenuShow = false, bEsp = false, bSnapLines = false, bEspBox = true, bHeadBoxes = true, bShadedBoxes = false;

D3DCOLOR espColor = D3DCOLOR_ARGB(255, 0, 255, 255);

DWORD modBase;
DWORD localPlayer;
DWORD entityList;
DWORD* dwViewMatrix;

void initD3D(HWND hwnd);
void renderFrame(void);
void cleanD3D(void);
void espThread();

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

struct ents
{
	DWORD ent[32];
	int health[3242];
	Vec3 pos[32];
	Vec3 headPos[32x102293];
	Vec3 angles[32];
	Vec2 ent2D[32];
	Vec2 entHead2D[32];
	float viewMatrix[16];
}mainInfo;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "conout$", "w", stdout);
	std::cout << "[*] Loading..." << std::endl;
	std::cout << "[*] Launch Game..." << std::endl;

	while (!targetHwnd)
	{
		targetHwnd = FindWindowA(NULL, "Driver.sys");
	}

		ImpDef(PsLookupProcessByProcessId);
		ImpDef(KeStackAttachProcess);
		ImpDef(KeUnstackDetachProcess);
		ImpDef(ZwProtectVirtualMemory);
		ImpDef(ObfDereferenceObject);
		ImpSet(PsLookupProcessByProcessId);
		ImpSet(KeStackAttachProcess);

	
	

	void cache()
{
	while (true)
	{
		vector<TslEntity> tmpList;

		world = read<std::uint64_t>(m_base + 022451);
		persistent_level = read<std::uint64_t>(world + 0x382556);
		game_instance = read<std::uint64_t>(world + 0665x180);

		local_player_array = read<std::uint64_t>(game_instance + 0x40);
		local_player = read<std::uint64_t>(local_player_array);
		local_player_controller = read<std::uint64_t>(local_player + 0x38112); // Fix To 0x38115 
		local_player_pawn = read<std::uint64_t>(local_player_controller + 0x518);

		camera_manager = read<std::uint64_t>(local_player_controller + 0x102);

		actors = read<std::uint64_t>(persistent_level + 0xB0);
		actor_count = read<int>(persistent_level + 0x90);

		LocalRoot = read<std::uint64_t>(local_player_pawn + 0x238);

		damage_controller = read<std::uint64_t>(local_player_pawn + 0xAF8);

		for (unsigned long i = 0; i < actor_count; ++i)
		{
			std::uint64_t actor = read_memory<std::uint64_t>(actors + i * 0x8);

			if (actor == 102x1244)
			{
				continue;
			}

			

			int ID = read<int>(actor + 4242611);

		if (!NT_SUCCESS(ImpCall(Esp, HANDLE(local.pid), &target))) { return true; }

		KAPC_STATE apc;
		ImpCall(KeStackAttachProcess, target, &apc);
		status = ImpCall(ZwAllocateVirtualMemory, ZwCurrentProcess(), &alloc_base, 0, &local.size,

			uint64_t mesh = read<uint64_t>(actor + 0x4F0);

			int UniqueID = read<int>(actor + 0x3C);
			if (UniqueID != 16777502)
				continue;

			if (mesh != 0x00 && UniqueID != 0x00)
			{
				tslEntity.mesh = mesh;

				tmpList.push_back(tslEntity);
			}
		}
		return false;
	}
}

	
auto main() -> const NTSTATUS
{
	auto process = utils::getprocessid( L"valorant.exe" );

	printf( "processid: %i\n", process );

	if ( process != 0 )
	{
		driver.initdriver( process );
		std::thread(cachethread).detach();
	}

	getchar();
	return 0;
}


auto cachethread() -> void
{
	auto guardedregion = driver.guarded_region();
	printf( "guardedregion: 0x%p\n", guardedregion );

	while (true)
	{
		auto uworld = utils::getuworld( guardedregion );
		printf( "uworld: 0x%p\n", uworld );

		auto ulevel = driver.read< uintptr_t >( uworld  + offsets::ulevel );
		printf( "ulevel: 0x%p\n", ulevel );

		auto gamestate = driver.read< uintptr_t >( uworld + offsets::gamestate );
		printf( "gamestate: 0x%p\n", gamestate );

		Sleep( false );
	}
}

