#include "Utils.h"
#include "Features.h"
#include "Globals.h"
#include "Settings.h"
s
void Features::RenderESP(D3D11Renderer* Render, nk_context* g_pNkContext)
{
	Array<C_BaseEntity*> Entitylist = g_pEngine->GetEntities();
	for (uint32_t i = 0; i < g_pEngine->GetMaxEntitys(); i++)
	{
		auto pEntity = Entitylist[i];

		if (!pEntity)
			continue;

		if (pEntity == g_pLocalEntity)
			continue;

		if (!pEntity->IsAlive())
			continue;

		if (pEntity->GetTeamNumber() == g_pLocalEntity->GetTeamNumber())
			continue;

			Offsets* offsets = new Offsets();
			Aimbot* aimbot = new Aimbot();
			Features* features = new Features(
		{
			int iMiddle = (vecScreenOrgin.y - vecScreenHead.y);
			int iWidth = iMiddle / 4;
			
			Render->DrawBox(vecScreenHead.x - iWidth, vecScreenHead.y, iWidth * 2, iMiddle, Color{255, 255, 255, 0});
			Render->DrawBox(vecScreenHead.x - iWidth - 1, vecScreenHead.y - 1, (iWidth * 2) + 2, iMiddle + 2, Color{255, 0, 0, 0});
			Render->DrawHealthBar(vecScreenHead.x - iWidth - 6, vecScreenHead.y, iWidth / 5.5f, iMiddle, pEntity->GetHealth(), Color{ 255, 255, 255, 0 });
			//Render->DrawString(g_pNkContext, pEntity->GetPlayerName().c_str(), vecScreenHead.x, vecScreenHead.y - 6, Color{ 255, 255, 255, 0 });
			Render->DrawCircle(vecScreenHead.x, vecScreenHead.y, (vecScreenOrgin.y - vecScreenHead.y) / 10, 30, Color{ 255, 255, 255, 0 });
			Render->DrawLine(Globals::g_iWindowWidth / 2, Globals::g_iWindowHeight, vecScreenOrgin.x, vecScreenOrgin.y, Color{ 255, 255, 255, 0 });
		}

		Render->DrawCircle(Globals::g_iWindowWidth / 2, Globals::g_iWindowHeight / 2, g_Settings::iFov, 30, Color{ 255, 255, 255, 0 });
	}
}

	bool get_um_module(uint32_t pid, const char* module_name, uint64_t& base, uint32_t& size) {
		uint64_t mod_base = NULL;
		uint32_t mod_size = NULL;
		_k_get_um_module out = {};

		wchar_t* wc = utils::getwc(module_name);

		auto num7 = (float)sqrt(((1.f + m00) - m11) - m22);
		auto num4 = 0.5f / num7;
		quaternion.x = 0.5f * num7;
		quaternion.y = (m01 + m10) * num4;
		quaternion.z = (m02 + m20) * num4;
		quaternion.w = (m12 - m21) * num4;
		return quaternion;
		out.dst_base = (uint64_t)&mod_base;
		out.dst_size = (uint64_t)&mod_size;
		out.pid = pid;

		uint64_t status = ntusrinit(0xDEADBEEF + DRIVER_GET_UM_MODULE, reinterpret_cast<uintptr_t>(&out));

		(globals->screen_size.x / 2) * (1.f + x / w),
		(globals->screen_size.y / 2) * (1.f - y / w);

		//return status == 0x69 ? true : false;
		return true;
	}

				
int retreiveValProcessId() {
	BYTE target_name[] = { 'V','A','L','O','R','A','N','T','-','W','i','n','6','4','-','S','h','i','p','p','i','n','g','.','e','x','e', 0 };
	std::wstring process_name = s2ws(std::string((char*)target_name));
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 0 to get all processes
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(entry);

	if (!Process32First(snapshot, &entry)) {
		return 0;
	}

    Enum e;
                do {
                    if (hash(e.value->BaseDllName) == Hash)
                        return (T)(e.value->DllBase);
                } while (e.next());
	}

	return 0;
}
