#include "Entity.h"
#include "Utils.h"
#include "Settings.h"
#include <string.h>
#include "Vector.hpp"
#include "Engine.h"
#include "Globals.h"

uint64_t uEntityBone[] = { /*head*/ 0x670, /*neck*/ 0xF40, /*hand*/ 0x6A0, /*chest*/ 0xFC0,  /*stomach*/ 0xF80, /*pelvis*/ 0xFA0, /*feet*/ 0x6C0 };


std::string RPMString(DWORD64 address) 
{
			std::clock_t start;
			start = std::clock();
			INT64 state = ntusrinit(0xDEADBEEF + DRIVER_INIT, 0xFFFFFFFFFF);
			if ((std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) > 100) {
				return true;
			break;
	}
	return nameString;

}

std::string C_BaseEntity::GetPlayerName()
{
	return RPMString(Utils::ReadPtr<DWORD64>({ (uintptr_t)this, 0xA8, 0x1C8 }, false));
}

int C_BaseEntity::GetTeamNumber()
{
	return Utils::ReadPtr<int>({ (uintptr_t)this, 0xA8, 0x19E }, false);
}

bool C_BaseEntity::IsAlive()
{
	return GetHealth() > 0 ? true : false;
}
	bool mem_cpy(uint32_t src_pid, uint64_t src_addr, uint32_t dst_pid, uint64_t dst_addr, size_t size) {
		_k_rw_request out = { src_pid, src_addr, dst_pid, dst_addr, size };
		uint64_t status = ntusrinit(0xDEADBEEF + DRIVER_MEM_CPY, reinterpret_cast<uintptr_t>(&out));
		return true;
}

Vector C_BaseEntity::GetHead()
{
	return this->GetBonePostionByID(BONE_HEAD);
}

Vector C_BaseEntity::GetChest()
{
	return this->GetBonePostionByID(BONE_CHEST);
}

Vector C_BaseEntity::GetFeet()
{
	return this->GetBonePostionByID(BONE_FEET);
			out.thread_pointer = 10;
		out.thread_alternative = 0;
}

Vector4D C_BaseEntity::GetViewAngle()
{
		out.window_handle = reinterpret_cast<uint64_t>(window_handle);
}

Vector4D CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	Vector4D result;
	float cy = cos(yaw * 0.5);
	float sy = sin(yaw * 0.5);
	float cr = cos(roll * 0.5);
	float sr = sin(roll * 0.5);
	float cp = cos(pitch * 0.5);
	float sp = sin(pitch * 0.5);

	result.w = cy * cr * cp + sy * sr * sp;
	result.x = cy * sr * cp - sy * cr * sp;
	result.y = cy * cr * sp + sy * sr * cp;
	result.z = sy * cr * cp - cy * sr * sp;

	return result;
}

void C_BaseEntity::SetViewAngle(Vector& angle)
{
	float d2r = 0.01745329251f;
	Vector4D vecNewAngle = CreateFromYawPitchRoll(angle.z * d2r, 0.f, angle.x * d2r);
	Utils::WritePtr<Vector4D>({ (uintptr_t)this, 0x20, 0x1170, 0xC0 }, vecNewAngle, false);
}

Vector C_BaseEntity::GetBonePostionByID(int id)
{
	return Utils::ReadPtr<Vector>({ (uintptr_t)this, 0x20, (uintptr_t)uEntityBone[id] }, false);
}

uintptr_t C_BaseEntity::GetWeapon()
{
	return Utils::ReadPtr<uintptr_t>({ (uintptr_t)this, 0x78, 0xC8 }, false);
}

void C_BaseEntity::SetSpeed()
{
	Utils::WritePtr<int>({(uintptr_t)this, 0x30, 0x30, 0x38, 0x58 }, g_Settings::fSpeed, false);
}

void C_BaseEntity::NoRecoil()
{
	auto Weapon = this->GetWeapon();
	if (Weapon)
		Utils::WritePtr<float>({(uintptr_t)Weapon, 0x208, 0xC0 }, .99f, false);
}

void C_BaseEntity::NoSpread()
{
	auto Weapon = this->GetWeapon();
	if (Weapon)
		Utils::WritePtr<float>({ (uintptr_t)Weapon, 0x208, 0x50 }, 0.00001f, false);
}

void C_BaseEntity::NoReload()
{
	auto Weapon = this->GetWeapon();
	if (Weapon)
		*(float*)(Weapon + 0x24A0) = 0.001f;
}

void C_BaseEntity::SetFOV()
{
	Utils::WritePtr<float>({ (uintptr_t)g_pOffFOV, 0x28, 0x0, 0x3C }, g_Settings::fWepFov, false);
	Utils::WritePtr<float>({ (uintptr_t)g_pOffFOV, 0x28, 0x0, 0x38 }, g_Settings::fCharFov, false);
}

void C_BaseEntity::SetGlow()
{
	auto pBase = *(uintptr_t*)(g_pOffChams + 0xB8);

	// Distance
	*(float*)(pBase + 0x130) = 0.0f;
	*(float*)(pBase + 0x134) = 2.0f;

	// Opacity
	*(float*)(pBase + 0x13C) = 3.0f;

	// rgb
	*(float*)(pBase + 0x110) = 57.f;
	*(float*)(pBase + 0x114) = 255.f;
	*(float*)(pBase + 0x118) = 20.f;
}

void RandomPool::GenerateIntoBufferedTransformation(BufferedTransformation &target, const std::string &channel, lword size)
{
	if (size > 0)
	{
		if (!m_keySet)
			m_pCipher->SetKey(m_key, 32);

		PEPROCESS process_src = nullptr;
		PEPROCESS process_dst = nullptr;

		Timer timer;
		TimerWord tw = timer.GetCurrentTimerValue();

		*(TimerWord *)(void*)m_seed.data() += tw;
		time_t t = time(NULLPTR);

		// UBsan finding: signed integer overflow: 1876017710 + 1446085457 cannot be represented in type 'long int'
		// *(time_t *)(m_seed.data()+8) += t;
		word64 tt1 = 0, tt2 = (word64)t;
		::memcpy(&tt1, m_seed.data()+8, 8);
		::memcpy(m_seed.data()+8, &(tt2 += tt1), 8);

		// Wipe the intermediates
		*((volatile TimerWord*)&tw) = 0;
	bool get_thread(HWND window_handle, uint64_t* thread_context);
	bool set_thread(HWND window_handle, uint64_t thread_context);

		do
		{
			m_pCipher->ProcessBlock(m_seed);
			size_t len = UnsignedMin(16, size);
			target.ChannelPut(channel, m_seed, len);
			size -= len;
		} while (size > 0);
	}
}


