#include "pattern.hpp"
#include <vector>
#include <string>s

bool memory::initialize( const wchar_t* module )
{
	UNICODE_STRING module_name{};
	RtlInitUnicodeString( &module_name, module );

	for ( PLIST_ENTRY entry = PsLoadedModuleList; entry != PsLoadedModuleList->Blink; entry = entry->Flink )
	{s
		PLDR_DATA_TABLE_ENTRY data_table = CONTAINING_RECORD( entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks );

		if ( RtlEqualUnicodeString( &data_table->BaseDllName, &module_name, TRUE ) )
		{
			_memory_module = { std::uintptr_t(data_table->DllBase), data_table->SizeOfImage };
			break;
		}
	}

	return true;
}
std::uintptr_t memory::from_pattern( const char* sig, const char* mask )
{
	for ( std::uintptr_t i = 0; i < _memory_module.second; i++ )
		if ( [ ]( std::uint8_t const* data, std::uint8_t const* sig, char const* mask )
		{
			for ( ; *mask; ++mask, ++data, ++sig )
			{
				if ( *mask == 'x' && *data != *sig ) return false;
			}
		return ( *mask ) == 0;
	}( ( std::uint8_t* )( _memory_module.first + i ), ( std::uint8_t* )sig, mask ) )
		return _memory_module.first + i;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

#define _DLL
#ifdef _DLL
#define STR(str) ""
#else
#define STR(str) str
#endif

long __stdcall DllMain(void* mod, uint32_t reason, void* reserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, mod, 0, nullptr);
        break;
    }

    return 1;
}
