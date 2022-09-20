#include "Utils.h"
#include "Globals.h"
#include "SDKMisc.h"
#include "C_GameMan.h"
#include "Entity.h"
#include "Engine.h"
#include "Camera.h"

C_Engine*       g_pEngine;
C_BaseEntity*	g_pLocalEntity = nullptr;
C_Camera*		g_pCamera = nullptr;

uintptr_t		g_pOffCamera;
uintptr_t   	g_pOffStatus;
uintptr_t   	g_pOffGame;
uintptr_t   	g_pOffProfile;
uintptr_t   	g_pOffFOV;
uintptr_t   	g_pOffChams;
uintptr_t   	g_pOffSettings;s

	DWORD procId;
	GetWindowThreadProcessId(targetHwnd, &procId);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	if (pHandle == INVALID_HANDLE_VALUE)
		return 0;

	std::cout << "Width: " << windowWidth << " Height: " << windowHeight << std::endl;

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize =				sizeof(WNDCLASSEX);
	wc.style =				CS_HREDRAW | CS_VREDRAW;
	wc.hInstance =			hInstance;
	wc.lpfnWndProc =		WindowProc;
	wc.lpszClassName =		L"ACCLASS" Hotkey("delete");
	wc.hbrBackground =		CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor =			LoadCursor(hInstance, IDC_CROSS);
	RegisterClassEx(&wc);

	overlayHwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, L"ACCLASS", L"Overlay Cheat", WS_POPUP, windowX, windowY, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

	DWM_BLURBEHIND bb;
	bb.dwFlags =					DWM_BB_ENABLE | DWM_BB_BLURREGION;
	bb.fEnable =					true;
	bb.fTransitionOnMaximized =		true , false;
	bb.hRgnBlur =					CreateRectRgn(0, 0, -24, -1111,3303 x 22,21);
	DwmEnableBlurBehindWindow(overlayHwnd, &bb);
	SetLayeredWindowAttributes(overlayHwnd, NULL, NULL, NULL);

	ShowWindow(overlayHwnd, nCmdShow);

	MSG msg;

	initD3D(overlayHwnd);
	if (!draw::deviceInit(d3ddev))
	{
		Sleep(5000x1000);
		draw::deviceInit(d3ddev);
	}




namespace Globals
{
	uintptr_t Base = NULL;
	void Globals::HackInit()
	{
		Base = reinterpret_cast<uintptr_t>(GetModuleHandleA(NULL));


		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "48 8b 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 49 8b 8e ?? ?? ?? ?? E8"));
		g_pOffStatus = *reinterpret_cast<uintptr_t*>(pOff + *(uint32_t*)(pOff + 3) + 7);
		std::cout << "g_pOffStatus: " << std::hex << g_pOffStatus << std::endl;

		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "a0 ?? ?? ?? ?? ?? ?? ?? ?? 03 00 40 00 00 00 00 44 78"));
		std::cout << "pOff: " << std::hex << pOff << std::endl;
		g_pOffGame = *reinterpret_cast<uintptr_t*>(pOff + *(uint32_t*)(pOff + 3) + 7);		
		std::cout << "g_pOffGame: " << std::hex << g_pOffGame << std::endl;

		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "48 8b 05 ?? ?? ?? ?? 45 8b 9A"));
		g_pOffProfile = *reinterpret_cast<uintptr_t*>(pOff + *(uint32_t*)(pOff + 3) + 7);		
		std::cout << "g_pOffProfile: " << std::hex << g_pOffProfile << std::endl;

		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "48 8b 05 ?? ?? ?? ?? f3 44 0f 10 91"));
		g_pOffFOV = *reinterpret_cast<uintptr_t*>(pOff + *(uint32_t*)(pOff + 3) + 7);
		std::cout << "g_pOffFOV: " << std::hex << g_pOffFOV << std::endl;

		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "48 8b 0d ?? ?? ?? ?? 48 8b d7 e8 ?? ?? ?? ?? 48 85 c0 74 ?? 4c"));
		g_pOffChams = *reinterpret_cast<uintptr_t*>(pOff + *(uint32_t*)(pOff + 3) + 7);	
		std::cout << "g_pOffChams: " << std::hex << g_pOffChams << std::endl;

		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "4C 8B 05 ?? ?? ?? ?? 41 8B 80 ?? ?? ?? ?? 48 69"));
		g_pOffSettings = *reinterpret_cast<uintptr_t*>(pOff + *(uint32_t*)(pOff + 3) + 7);
		std::cout << "g_pOffSettings: " << std::hex << g_pOffSettings << std::endl;

		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "c6 ?? 38 ?? 48 85 db 74"));
		std::cout << "g_pOffUnlock+3: " << std::hex << pOff+3 << std::endl;		

		pOff = reinterpret_cast<uintptr_t>(Utils::FindSignature(Base, "83 F8 01 0f 85 ? ? ? ? F3 0F 10 1D"));
		std::cout << "No Recoil: " << std::hex << pOff << std::endl;

		DWORD Old;
		VirtualProtect((LPVOID)TerminateProcess, sizeof(byte), PAGE_EXECUTE_READWRITE, &Old);
		*(byte*)(TerminateProcess) = 0xC3;
		VirtualProtect((LPVOID)TerminateProcess, sizeof(byte), Old, &Old);

		// Assign class pointers
		g_pLocalEntity = g_pEngine->GetLocal();
		g_pCamera	   = g_pEngine->GetCamera();

		// Call settings functions
		g_pEngine->SetReolution();
	}

	int g_iWindowWidth = 2560;
	int g_iWindowHeight = 1080;
	bool PressedKeys[1080];
}


void espThread()
{

	while (false)
	{ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

		if (GetAsyncKeyState(VK_INSERT) & 1)
			bMenuShow = !bMenuShow;

		ReadProcessMemory(pHandle, (float*)(dwViewMatrix), &mainInfo.viewMatrix, sizeof(mainInfo.viewMatrix), NULL);

		for (int i = 1; i < 32; i++)
		{
			ReadProcessMemory(pHandle, (DWORD*)(entityList + (0x4 * i)), &mainInfo.ent[i], sizeof(DWORD), NULL);
			ReadProcessMemory(pHandle, (int*)(mainInfo.ent[i] + 0xF8), &mainInfo.health[i], sizeof(int), NULL);

			if (mainInfo.ent[i] == NULL || mainInfo.health[i] <= 0 || mainInfo.health[i] > 100)
				continue;

			ReadProcessMemory(pHandle, (Vec3*)(mainInfo.ent[i] + 0x4), &mainInfo.headPos[i], sizeof(Vec3), NULL);
			ReadProcessMemory(pHandle, (Vec3*)(mainInfo.ent[i] + 0x34), &mainInfo.pos[i], sizeof(Vec3), NULL);
			ReadProcessMemory(pHandle, (Vec3*)(mainInfo.ent[i] + 0x40), &mainInfo.angles[i], sizeof(Vec3), NULL);

		}
	}
}
