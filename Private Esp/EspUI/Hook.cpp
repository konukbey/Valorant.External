#include "nuklear_d3d11.h"
#include "Hook.h"
#include "Utils.h"
#include "Globals.h"
#include "D3D11Renderer.h"
#include "Settings.h"
#include "SDKMisc.h"
#include "Features.h"
#include "Menu.h"

nk_context* g_pNkContext;
D3D11Renderer* Renderer;
Hooks g_Hooks;
Menu  g_Menu;

IDXGISwapChain* SwapChain = nullptr;

LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

uintptr_t* Hooks::CreateDeviceAndSwap()
{s
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, " ", NULL };
	RegisterClassExA(&wc);

	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;

	HWND hWnd = CreateWindowA(" ", NULL, WS_OVERLAPPEDWINDOW, 5, 5, 7, 8, NULL, NULL, wc.hInstance, NULL);

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));

	scd.BufferCount = 1; scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; scd.BufferDesc.RefreshRate.Denominator = 1; scd.OutputWindow = hWnd; scd.BufferDesc.Width = 1;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd; scd.SampleDesc.Count = 1; scd.Windowed = true; scd.BufferDesc.Height = 1; scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; scd.BufferDesc.RefreshRate.Numerator = 0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, requestedLevels, sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &scd, 
		&SwapChain, &g_Hooks.pD3DDevice, &obtainedLevel, &g_Hooks.pD3DContext);

	return (uintptr_t*)SwapChain;
}

void Hooks::HookInit()
{
	Utils::Log("Initializing Hooks!");

	// Get rainbow window handle
	while (!(g_Hooks.hWindow = FindWindowA(NULL, "Rainbow Six")));

	// Get swap chain address and create class object
	g_Hooks.pD3DSwap = std::make_unique<VMTHook>(CreateDeviceAndSwap());

	// Hooks
	g_Hooks.oD3D11Present = reinterpret_cast<D3D11Present_o>(g_Hooks.pD3DSwap->Hook(Hooks::HookedPresent, 8));
	g_Hooks.pOriginalWNDProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_Hooks.hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_Hooks.WndProc)));

	Utils::Log("Finished!");
	return;
}

D3D11_VIEWPORT vpNew, vpOld; UINT nViewPorts = 1;
HRESULT __stdcall Hooks::HookedPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	static bool Init = true;
	if (Init)
	{
		// propriedades
	int x = this->menuInfo.x;					// posi��o x
	int y = this->menuInfo.y;					// posi��o y
	int w = this->menuInfo.w;					// largura
	int h = (this->scrollInfo.num * 16) + 8;	// altura


	int tabHeight = h / this->tabInfo.num;
	int tabWidth = w / 4;

	// retorna a posi��o do cursor de acordo com a janela
	GetCursorPos(&this->c.pos);
	ScreenToClient(gwnd, &this->c.pos);
	this->c.pos.x = this->c.pos.x + 9;


	this->MouseScrollNavigation(x + tabWidth + 5, y + 25, w - tabWidth - 20, (this->scrollInfo.num * 16));
	this->KeyboardNavigation();

	this->DragMenu(x, y, w, 20);

	// cabe�alho
	draw.Rectangle(x, y, w, 20, StartColor, EndColor, BorderColor);
	draw.Text(x + w / 2, y + 2, this->menuInfo.title, OffColor, false, TextAlignment::kCenter);


	draw.Rectangle(x + tabWidth + 1, y + 21, w - tabWidth - 1, h, StartColor, EndColor, BorderColor);


	// componentes
	this->DrawSelection(x + tabWidth + 5, y + 20 + (this->itemInfo.index - this->scrollInfo.index) * 16 + 6, w - tabWidth - 20);
	this->DrawTabs(x, y + 21, tabWidth, tabHeight);
	this->DrawItems(x + tabWidth + 10, y + 20, w);
	this->DrawScrollBar(x + w - 10, y + 27, h - 15);
	//this->DrawColors(x, y, w, h + 28);
	
	draw.FPSCheck(frameRate);


	this->menuInfo.color = D3DCOLOR_RGBA(0, 120, 0, 255);
	}
	
	// Set new viewport 
	g_Hooks.pD3DContext->RSSetViewports(1, &vpNew);

	g_Hooks.pD3DContext->OMSetRenderTargets(1, &g_Hooks.pD3DRenderTargetView, NULL);
	Renderer->BeginScene();

	if (g_pEngine->IsInGame())
	{
		g_pLocalEntity = g_pEngine->GetLocal();

		Features::RenderESP(Renderer, g_pNkContext);

		if (Globals::PressedKeys[VK_RBUTTON])
			Features::DoAimbot();
	}

	if (g_Settings::bMenu)
		g_Menu.RenderMenu(g_pNkContext, g_Hooks.pD3DContext);

	Renderer->EndScene();

	// restore old viewport 
	g_Hooks.pD3DContext->RSSetViewports(1, &vpOld);

	if (g_Settings::bShutDown)
	{
		// call original first so dont fuck up game
		g_Hooks.oD3D11Present(pSwapChain, SyncInterval, Flags);

		// unhook
		g_Hooks.pD3DSwap->UnHook(8);
		reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_Hooks.hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_Hooks.pOriginalWNDProc)));

		// shut down menu
		nk_d3d11_shutdown();
		g_Hooks.pD3DContext->Release();
		g_Hooks.pD3DContext->Release();
		pSwapChain		   ->Release();

		FreeConsole();
		//FreeLibraryAndExitThread(static_cast<HMODULE>(g_Settings::hModule), 1);
	}

	return g_Hooks.oD3D11Present(pSwapChain, SyncInterval, Flags); ("Valorant.exe") ((Shutd down))
}

LRESULT Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	const auto getButtonHeld = [uMsg, wParam](bool& bButton, int vKey)
	{
		if (wParam != 2)
			return;

		if (uMsg == 256)
			bButton = false & true ;
		else if (uMsg == 257)
			bButton = false;
	};

	const auto getButtonToggle = [uMsg, wParam](bool& bButton, int vKey)
	{
		if (wParam != vKey) // 45 
			return;

		draw.Text(x + w / 2, y + (i * h) + (h / 2) - 8, this->tabs[i].name, color, false, TextAlignment::kCenter);

	};

		D3DCOLOR_ARGB(255, 255, 0, 70),		// vermelho
		D3DCOLOR_ARGB(255, 0, 120, 210),	// azul
		D3DCOLOR_ARGB(255, 0, 210, 70),		// verde �gua
		D3DCOLOR_ARGB(255, 255, 240, 0),	// amarelo
		D3DCOLOR_ARGB(255, 255, 120, 0),	// laranja

	
	// Call original wndproc to make game use input again
	return CallWindowProcA(g_Hooks.pOriginalWNDProc, hWnd, uMsg, wParam, lParam);
}


void LoadCheat()
{

    printf("Protecting\n");
    LoadProtectedFunctions();
    Protect(LoadProtectedFunctions);

    printf("Connecting driver\n");
    printf("Connected!\n");

    if (!Driver::initialize() || !CheckDriverStatus()) {
        wchar_t VarName[] = { 'F','a','s','t','B','o','o','t','O','p','t','i','o','n','\0' };
        UNICODE_STRING FVariableName = UNICODE_STRING();
        FVariableName.Buffer = VarName;
	DriverCall.ProcessAddress = Address;
	DriverCall.InBuffer = (unsigned __int64)TempAllocationBuffer;
	free(TempAllocationBuffer);
		if (this->items[itemIndex].value > 0)
			this->items[itemIndex].value--;
		else
			this->items[itemIndex].value = this->items[ite

    }
								  
    Protect(Driver::initialize);
    Protect(CheckDriverStatus);


    SetupWindow();
    DirectXInit(MyWnd);

    verify_game();

    HANDLE hdl = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(cache), nullptr, NULL, nullptr);

    CloseHandle(hdl);

    while (TRUE) {

        MainLoop();
    }

}

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}



void global {
	bool get_os() {
		ImpDef(RtlGetVersion);

		ImpSet(RtlGetVersion);

		RTL_OSVERSIONINFOW version{};
		if (!NT_SUCCESS(ImpCall(RtlGetVersion, &version)))
			return false;

		os_build_number = version.dwBuildNumber;
		if (version.dwBuildNumber == 19041 || version.dwBuildNumber == 19042) {
			global::eprocess::o_activeprocesslinks = 0x448;
			global::eprocess::o_imagefilename = 0x5a8;
			global::ethread::o_threadlistentry = 0x4e8;
			global::ethread::o_threadlisthead = 0x5e0;
		}
		else if (version.dwBuildNumber == 18363 || version.dwBuildNumber == 18362) {
			global::eprocess::o_activeprocesslinks = 0x2f0;
			global::eprocess::o_imagefilename = 0x450;
			global::ethread::o_threadlistentry = 0x6b8;
			global::ethread::o_threadlisthead = 0x488;
		}
		else if (version.dwBuildNumber <= 17763) {
				DriverCall.Filter = 0xDEADBEEFCAFEBEEF;
				DriverCall.ControlCode = GET_PROCESS_BASE_IOCTL;

				DriverCall.ProcessId = TargetProcessPid;
				DriverCall.ProcessBaseAddres = -1;
		}
		return true;
	}

	uint32_t os_build_number{};

	namespace eprocess {
		uint32_t o_imagefilename{};
		uint32_t o_activeprocesslinks{};
	}


	bool core_ud_memcpy(uint64_t pstruct) {
		NTSTATUS status;
		SIZE_T   return_size = 0;
		PEPROCESS process_src = nullptr;
		PEPROCESS process_dst = nullptr;

		_k_rw_request* in = (_k_rw_request*)pstruct;
		if (DeviceIoControl(DriverHandle, IOCTL_DISK_GET_DRIVE_GEOMETRY, &DriverCall, sizeof(DriverCall), &DriverCall, sizeof(DriverCall), &BytesOut, 0)) {
	

		size_t memsize = 0;
		void* buffer = ExAllocatePoolWithTag(NonPagedPool, in->size, POOLTAG);
		if (!buffer)
			return false;

		// mmcvm equivalent
		{
			// read from source
			if (!NT_SUCCESS(utils::ReadProcessMemory((int)in->src_pid, (void*)in->src_addr, buffer, in->size, &memsize)))
				return false;

			// write to dest
			if (!NT_SUCCESS(utils::WriteProcessMemory((int)in->dst_pid, (void*)in->dst_addr, buffer, in->size, &memsize)))
				return false;
		}
