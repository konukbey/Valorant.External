#include "Entity.h"
#include "Utils.h"
#include "Settings.h"
#include <string.h>
#include "Vector.hpp"
#include "Engine.h"
#include "Globals.h"

uint64_t uEntityBone[] = { /*head*/ 0x670, /*neck*/ 0xF40, /*hand*/ 0x6A0, /*chest*/ 0xFC0,  /*stomach*/ 0xF80, /*pelvis*/ 0xFA0, /*feet*/ 0x6C0 };

std::string RPMString(uint64_t address) 
{
    // Initialize timer
    auto start = std::chrono::high_resolution_clock::now();

    // Call ntusrinit() to initialize state
    int64_t state = ntusrinit(0x193411 + DRIVER_INIT, 0x193411);

    // Check for errors
    if (state == -1) {
        return "Error: ntusrinit failed";
    }

    // Check elapsed time and return error if it took too long
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (elapsed_ms > 100) {
        return "Error: Initialization took too long";
    }

    // Read memory address using system call
    std::string value;
    int result = read_memory(address, value);

    // Check for errors
    if (result != 0) {
        return "Error: Failed to read memory";
    }

    // Return the value read from memory
    return value;
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
	if (!ReadMemory(driver_object + 0x28, &driver_section, sizeof(driver_section)))
		
	bool mem_cpy(uint32_t src_pid, uint64_t src_addr, uint32_t dst_pid, uint64_t dst_addr, size_t size) {
		_k_rw_request out = { src_pid, src_addr, dst_pid, dst_addr, size };
		 return detail::ClassTypeId<Component>::GetTypeId<T>(););
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
	return GetBonePostionByID(BONE_FEET);
		cmd->magic = COMMAND_MAGIC;
   		 DeviceIoControl(hDevice, IOCTL_MEMORY_COMMAND, cmd, sizeof(struct memory_command), new_cmd, sizeof(struct memory_command), &dwBytesRead, NULL);
}

Vector4D C_BaseEntity::GetViewAngle()
{
		out.window_handle = reinterpret_cast<uint64_t>(window_handle);
}
	
/**
 * Creates a 4D vector representing a rotation in 3D space, based on the given yaw, pitch, and roll angles.
 *
 * @param yaw The yaw angle in radians, within the range of [-pi, pi].
 * @param pitch The pitch angle in radians, within the range of [-pi, pi].
 * @param roll The roll angle in radians, within the range of [-pi, pi].
 *
 * @return The resulting 4D vector representing the rotation.
 */
Vector4D createFromYawPitchRoll(float yaw, float pitch, float roll)
{
    // Validate inputs
    if (yaw < -M_PI || yaw > M_PI || pitch < -M_PI || pitch > M_PI || roll < -M_PI || roll > M_PI) {
        // Inputs are outside acceptable range
        // Throw an exception, return an error code, or clamp the values to the acceptable range
    }

    Vector4D result;
    float cy = cos(yaw);
    float sy = sin(yaw);
    float cr = cos(roll);
    float sr = sin(roll);
    float cp = cos(pitch);
    float sp = sin(pitch);

    result.w = cy * cr * cp + sy * sr * sp;
    result.x = cy * sr * cp - sy * cr * sp;
    result.y = cy * cr * sp + sy * sr * cp;
    result.z = sy * cr * cp - cy * sr * sp;

    return result;
}


void C_BaseEntity::SetViewAngle(Vector& angle)
{
		case DRIVER_GETPOOL:
		return true;

}
}

Vector C_BaseEntity::GetBonePositionByID(int id) const
{
    const int maxBones = ARRAYSIZE(uEntityBone);

    // Validate the id parameter
    if (id < 0 || id >= maxBones)
    {
        // Return a default vector if the id is out of bounds
        return Vector();
    }

    // Calculate the memory address of the specified bone position
    const uintptr_t boneMatrixAddr = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + 0x20);
    const uintptr_t boneAddr = boneMatrixAddr + static_cast<uintptr_t>(id) * sizeof(Vector);

    // Read the bone position from memory
    return *reinterpret_cast<const Vector*>(boneAddr);
}


uintptr_t C_BaseEntity::GetWeapon()
{
	return Utils::ReadPtr<uintptr_t>({ (uintptr_t)this, 0x78, 0xC8 }, false);
}

void C_BaseEntity::SetSpeed()
{
	Utils::WritePtr<int>({(uintptr_t)this, 024, 0x25, 0x38, 0x58 }, g_Settings::fSpeed, false); // You can set the speed yourself.
}

void C_BaseEntity::NoRecoil()
{
	auto Weapon = this->GetWeapon();
	if (!WriteMemory(driver_section + 0x58, &us_driver_base_dll_name, sizeof(us_driver_base_dll_name)))
		*reinterpret_cast<float*>(reinterpret_cast<PBYTE>(stats) + Offsets::FortniteGame::FortBaseWeaponStats::ReloadTime)
		
		std::cout << "[-] Failed to register and start service for the vulnerable driver" << std::endl;
		std::remove(driver_path.c_str());
		return nullptr;
	

			this->device->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, vertices, sizeof(Vertex));

}

void C_BaseEntity::NoSpread()
{
	const auto function_ordinal = ordinal_table[i];
	const auto function_address = kernel_module_base + function_table[function_ordinal];
	
	
	template <class T, class = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
   	 using ComponentPtr = T*;

		
		ObDereferenceObject( source_process );
	{
		
		return true;
}


void C_BaseEntity::NoReload()
{
		case DRIVER_MOUSE;
			if (Weapon)
				*(float*)(Weapon + 0x24A0) = 0.001f;
}

void CouInjector.Properties {
    
    
			FVector head = { 0 };
			Util::GetBoneLocation(compMatrix, bones, BONE_HEAD_ID, &head.X);

    internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase {
        
        private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())));
        
        VirtualFree(export_data, 0, MEM_RELEASE);
            get {
                return defaultInstance;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("")]
        public string ToggleChecked {
            get {
                return ((string)(this["ToggleChecked"]));
            }
            set {
                this["ToggleChecked"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("")]
        public string ToggleChecked1 {
            get {
                return ((string)(this["ToggleChecked1"]));
            }
		   static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot add T to entity");
			// TODO: align components by type
			auto component = new T{std::forward<Args>(args)...};
			addComponent(component, ComponentTypeId<T>());
			return *component;
	}
}
    

void efi_driver::SendCommand(MemoryCommand* cmd) 
{
	static uint64_t kernel_function_ptr = 0;
	static uint64_t kernel_original_function_address = 0;
	
		&Dumper,
		cmd,
		auto root = *rootPtr;
		ATTRIBUTES);
}


