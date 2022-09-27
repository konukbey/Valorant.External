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
bool bMenuShow = false, bEsp = false, bSnapLines = false, bEspBox = false, bHeadBoxes = false, bShadedBoxes = false;

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
	int health[32];
	Vec3 pos[32];
	Vec3 headPos[32];
	Vec3 angles[32];
	Vec2 ent2D[32];
	Vec2 entHead2D[32];
	float viewMatrix[16];
	char entName[16];
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
		targetHwnd = FindWindowA(NULL, "AssaultCube");
	}

	RECT rect;
	GetWindowRect(targetHwnd, &rect);
	windowWidth = rect.right - rect.left;
	windowHeight = rect.bottom - rect.top;
	windowX = rect.left;
	windowY = rect.top;
	vecScreen.x = windowWidth / 2;
	vecScreen.y = windowHeight;
	
	

	void cache()
{
	while (true)
	{
		vector<TslEntity> tmpList;

		world = read<std::uint64_t>(m_base + 0x5DD8EF8);
		persistent_level = read<std::uint64_t>(world + 0x38);
		game_instance = read<std::uint64_t>(world + 0x180);

		local_player_array = read<std::uint64_t>(game_instance + 0x40);
		local_player = read<std::uint64_t>(local_player_array);
		local_player_controller = read<std::uint64_t>(local_player + 0x38);
		local_player_pawn = read<std::uint64_t>(local_player_controller + 0x518);

		camera_manager = read<std::uint64_t>(local_player_controller + 0x530);

		actors = read<std::uint64_t>(persistent_level + 0xB0);
		actor_count = read<int>(persistent_level + 0xB8);

		LocalRoot = read<std::uint64_t>(local_player_pawn + 0x238);
		LocalPos = read<Vector3>(LocalRoot + 0x1E0);

		damage_controller = read<std::uint64_t>(local_player_pawn + 0xAF8);

		for (unsigned long i = 0; i < actor_count; ++i)
		{
			std::uint64_t actor = read<std::uint64_t>(actors + i * 0x8);

			if (actor == 0x00)
			{
				continue;
			}

			

			int ID = read<int>(actor + 0x18);

			TslEntity tslEntity{ };
			tslEntity.pObjPointer = actor;
			tslEntity.ID = ID;
			tslEntity.PlayerController = local_player_controller;

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
		entityList = tmpList;
		Sleep(1);
	}
}
