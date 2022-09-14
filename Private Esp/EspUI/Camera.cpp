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
