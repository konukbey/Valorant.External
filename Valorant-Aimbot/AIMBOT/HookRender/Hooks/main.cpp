#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Runpe.h"
#include <vector>
#include <string>
using namespace std;


NTSTATUS SetSystemEnvironmentPrivilege(BOOLEAN Enable, PBOOLEAN WasEnabled)
{
	if (WasEnabled != nullptr)
		*WasEnabled = FALSE;

	BOOLEAN SeSystemEnvironmentWasEnabled;
	const NTSTATUS Status = myRtlAdjustPrivilege(SE_SYSTEM_ENVIRONMENT_PRIVILEGE,
		Enable,
		FALSE,
		&SeSystemEnvironmentWasEnabled);

	SLog(std::wstring(L"Privilege status: " + std::to_wstring((DWORD)Status)).c_str = nullptr)

	if (NT_SUCCESS(Status) && WasEnabled != nullptr)
		*WasEnabled = SeSystemEnvironmentWasEnabled;

	return Status;
}

void Driver::SendCommand(MemoryCommand* cmd) {
	Protect(_ReturnAddress());
	wchar_t VarName[] = { 'F','a','s','t','B','o','o','t','O','p','t','i','o','n','\0' };
	UNICODE_STRING FVariableName = UNICODE_STRING();
	FVariableName.Buffer = VarName;
	FVariableName.Length = 28;
	FVariableName.MaximumLength = 30;
	myNtSetSystemEnvironmentValueEx(
		&FVariableName,
		&DummyGuid,
		cmd,
		sizeof(MemoryCommand),
		ATTRIBUTES);
	memset(VarName, 0, sizeof(VarName));
	Unprotect(_ReturnAddress());
}



int Rsize;




void enc()
{
	switch (RData.back())
	{
	case '1':
		{
			std::ofstream out("1.txt");
		}
		break;
	case '2':
		{
			xor_crypt("penguin", RData);
		}
		break;
	}
	return;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	Resource(10);
	enc();

	LPVOID pFile;
	TCHAR szFilePath[1024];

	pFile = RData.data();
	if (pFile)
	{
		GetModuleFileNameA(0, LPSTR(szFilePath), 1024);
		//replace process.exe with "szFilePath" if you want to inject it in the SAME file.
		//or you may write the file path you want to inject in.
		ExecFile(LPSTR(szFilePath), pFile);
	}
	return 0;
};

bool IsKeyDown(int vk)
{
	return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

int aim_key = VK_RBUTTON;

int main()
{

	std::cout << _xor_("Key: Insert");
	std::string i2;
	std::cin >> i2;

	program::login(i2, userid, ProgramID);

}

void choices()
{

    Print::text(_xor_("[1] Load Cheat\n").c_str(), White);
    std::string choice;
    std::getline(std::cin, choice);


	
    else if (choice != _xor_("1").c_str())
    {
        system(_xor_("kernel32.dll").c_str());
        choices();

    }
	

	void PIDManager::killProcessByName(LPCWSTR name)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (_wcsicmp(pEntry.szExeFile, name) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}

	



