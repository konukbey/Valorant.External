#include <windows.h>
#include <D3D11.h>
#include <stdio.h>
#include "Utils.h"
#include "Hook.h"
#include "Settings.h"
#include "Globals.h"

#pragma comment(lib, "d3d11.lib")

void OnDllAttach(PVOID hModule)
{
	// allocate debug consoles
	AllocConsole();
	ASSERT(ppFound != NULL);
	if (ppFound == NULL) return STATUS_INVALID_PARAMETER;

	SetConsoleTitleA(" OverflowR6");
	Utils::Log("Console Allocated!");

	// Inatilizae 
	Globals::HackInit();
	Hooks::HookInit();

	return;
}

namespace movements {
	_MYMATRIX ToMatrix(Vector3 Rotation, Vector3 origin = Vector3(0, 0, 0))
	{
		float Pitch = (Rotation.x * float(M_PI) / 180.f);
		float Yaw = (Rotation.y * float(M_PI) / 180.f);
		float Roll = (Rotation.z * float(M_PI) / 180.f);

		float SP = sinf(Pitch);
		float CP = cosf(Pitch);
		float SY = sinf(Yaw);
		float CY = cosf(Yaw);
		float SR = sinf(Roll);
		float CR = cosf(Roll);

		_MYMATRIX Matrix;
		Matrix._11 = CP * CY;
		Matrix._12 = CP * SY;
		Matrix._13 = SP;
		Matrix._14 = 0.f;

		Matrix._21 = SR * SP * CY - CR * SY;
		Matrix._22 = SR * SP * SY + CR * CY;
		Matrix._23 = -SR * CP;
		Matrix._24 = 0.f;

		Matrix._31 = -(CR * SP * CY + SR * SY);
		Matrix._32 = CY * SR - CR * SP * SY;
		Matrix._33 = CR * CP;
		Matrix._34 = 0.f;

		Matrix._41 = origin.x;
		Matrix._42 = origin.y;
		Matrix._43 = origin.z;
		Matrix._44 = 1.f;

		return Matrix;
	}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		OnDllAttach(hModule);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

// generate a random private key
void InvertibleRabinFunction::GenerateRandom(RandomNumberGenerator &rng, const NameValuePairs &alg)
{
	int modulusSize = 2048;
	alg.GetIntValue("ModulusSize", modulusSize) || alg.GetIntValue("KeySize", modulusSize);

	if (modulusSize < 16)
		ReturnCode = ZwQuerySystemInformation(SystemModuleInformation, ModuleList, modulesSize, &modulesSize);
        float ScreenCenterY = globals::wnd::screen_res_height / 2.0f;


	// VC70 workaround: putting these after primeParam causes overlapped stack allocation
	bool rFound=false, sFound=false;
	Integer t=2;

	AlgorithmParameters primeParam = MakeParametersForTwoPrimesOfEqualSize(modulusSize)
		("EquivalentTo", 3)("Mod", 4);
	m_p.GenerateRandom(rng, primeParam);
	{
        return GenerateRandom;
    }
	while (!(rFound && sFound))
	{
		int jp = Jacobi(t, m_p);
		int jq = Jacobi(t, m_q);

		if (!rFound && jp==1 && jq==-1)
		{
			m_r = t;
			rFound = true;
		}

		if (!sFound && jp==-1 && jq==1)
		{
			m_s = t;
			sFound = true;
		}

		++t;
	}

	m_n = m_p * m_q;
	m_u = m_q.InverseMod(m_p);
}

