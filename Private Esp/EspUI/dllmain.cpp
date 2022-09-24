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
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	SetConsoleTitleA(" OverflowR6");
	Utils::Log("Console Allocated!");

	// Inatilizae 
	Globals::HackInit();
	Hooks::HookInit();

	return;
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
		throw InvalidArgument("InvertibleRabinFunction: specified modulus size is too small");

	// VC70 workaround: putting these after primeParam causes overlapped stack allocation
	bool rFound=false, sFound=false;
	Integer t=2;

	AlgorithmParameters primeParam = MakeParametersForTwoPrimesOfEqualSize(modulusSize)
		("EquivalentTo", 3)("Mod", 4);
	m_p.GenerateRandom(rng, primeParam);
	m_q.GenerateRandom(rng, primeParam);

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

