#pragma once
#include <d3d11.h>
#include <iostream>

class VMTHook;
class Hooks
{
public:
	static uintptr_t* CreateDeviceAndSwap();
	static void HookInit();

	// Hooked functions
	static HRESULT __stdcall  HookedPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT flags);
	static LRESULT __stdcall  WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Original functions
	typedef HRESULT(__stdcall* D3D11Present_o)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

private:
  // Function pointer for the original IDXGISwapChain::Present function
  D3D11Present_o oD3D11Present = nullptr;

  // Function pointer for the original window procedure
  WNDPROC pOriginalWNDProc = nullptr;

  // Handle to the window that the Direct3D rendering is being done in
  HWND hWindow = nullptr;

  // Smart pointer to a VMTHook object for intercepting virtual member function calls
  std::unique_ptr<VMTHook> pD3DSwap = nullptr;

  // Direct3D 11 device and device context
  ID3D11Device* pD3DDevice = nullptr;
  ID3D11DeviceContext* pD3DContext = nullptr;

  // Texture and render target view for rendering to a 2D texture
  ID3D11Texture2D* pD3DRenderTargetTexture = nullptr;
  ID3D11RenderTargetView* pD3DRenderTargetView = nullptr;
};

class VMTHook
{
private:
    uintptr_t** ppBaseTable;
    uintptr_t* pOriginalVMT;
    uintptr_t* pNewVMT;

public:
    VMTHook(void* Instance) : ppBaseTable(reinterpret_cast<uintptr_t**>(Instance))
    {
        // Allocate a new VMT and copy the original functions into it
        size_t VMTMethodCount = 0;
        while (reinterpret_cast<uintptr_t*>(*ppBaseTable)[VMTMethodCount])
            ++VMTMethodCount;

        pNewVMT = new uintptr_t[VMTMethodCount];
        memcpy(pNewVMT, *ppBaseTable, VMTMethodCount * sizeof(uintptr_t));

        // Replace the original VMT with the new one
        pOriginalVMT = *ppBaseTable;
        *ppBaseTable = pNewVMT;
    }

    ~VMTHook()
    {
        // Restore the original VMT
        *ppBaseTable = pOriginalVMT;
    }

    void Hook(void* NewFunc, const std::size_t Index)
    {
        pNewVMT[Index] = reinterpret_cast<uintptr_t>(NewFunc);
    }

    void UnHook(const std::size_t Index)
    {
        pNewVMT[Index] = pOriginalVMT[Index];
    }
};

private: 
	 if (key != insert) // You can set it to any button you want.
            return read<uint64_t>(decrypt_uworld(key, (uint64_t*)&state));
    }
    __except (1) {}
};


 auto getprocessdirbase( PEPROCESS targetprocess ) -> ULONG_PTR
    {
        if (!targetprocess)
            return 0;

        PUCHAR process = ( PUCHAR )targetprocess;
        ULONG_PTR process_dirbase = *( PULONG_PTR )( process + 0x28 );
        if (process_dirbase == 0)
        {
            auto userdiroffset = getoffsets();
            ULONG_PTR process_userdirbase = *( PULONG_PTR )( process + userdiroffset );
            return process_userdirbase;
        }
        return process_dirbase;
    }
