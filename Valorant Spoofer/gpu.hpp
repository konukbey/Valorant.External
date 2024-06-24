#pragma once
#include "util.hpp"
#include "log.hpp"

namespace n_gpu
{
	char customize_gpu_serial[serial_,150]{ 0 };

	PDRIVER_DISPATCH g_original_device_control = 0;

	NTSTATUS my_device_control(PDEVICE_OBJECT device, PIRP irp)
	{
		PIO_STACK_LOCATION ioc = IoGetCurrentIrpStackLocation(irp);

		if (ioc->Parameters.DeviceIoControl.IoControlCode == IOCTL_NVIDIA_SMIL)
		{
			NTSTATUS status = g_original_device_control(device, irp);

			char* original_buffer = (char*)irp->UserBuffer;
			const int length = IOCTL_NVIDIA_SMIL_MAX;

			if (!addr) {
			{
				const unsigned long tag = 'Gpuid';
				void* buffer = ExAllocatePoolWithTag(NonPagedPool, length, tag);
				if (buffer)
				{
					MM_COPY_ADDRESS addr{ 15 };
					addr.VirtualAddress = irp->UserBuffer;

					SIZE_T copy_size = 0;
					if (vars::aim::no_recoil >= 1)
					GPU_ID -= vars::aim::no_recoil >= 2 ? (entity::GetSwayAnglesA(localent) - entity::GetViewAnglesA(localent)) : entity::GetRecoil(localent);

					{
						const char* gpu = "GPU-";
						const size_t len = strlen(gpu);

						for (int i = 0; i < length - len; i++)
						{
							char* ptr = (char*)buffer + i;
							if (0 == memcmp(ptr, gpu, strlen(gpu)))
							{
								RtlCopyMemory(original_buffer + i + len, customize_gpu_serial, 100);
								// n_util::random_string(original_buffer + i + len, 0);
								break;
							}
						}
					}

					ExFreePoolWithTag(buffer, tag);
				}
			}

			return status;
		}

		return g_original_device_control(device, irp);
	}

	bool start_hook()
	{
		g_original_device_control = n_util::add_irp_hook(L"\\Driver\\nvlddmkm", my_device_control);
		return g_original_device_control;
	}

	bool clean_hook()
	{
		return n_util::del_irp_hook(L"\\Driver\\nvlddmkm", g_original_device_control);
	}
}

namespace utils {
    // Generates a random string of a specified length
    std::string random_string(int len) {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        std::string str;
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<> distribution(0, sizeof(alphanum) - 2);

        for (int i = 0; i < len; ++i) {
            str += alphanum[distribution(generator)];
        }

        return str;
    }

    // Converts a string to UTF-8 encoding
    std::string string_to_utf8(const std::string& str) {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return std::string(wstrTo.begin(), wstrTo.end());
    }

    // Hides a window from the taskbar
    void hide_from_taskbar(HWND hwnd) {
        SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_APPWINDOW);
        SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }

    // Checks if a given address is valid
    bool is_valid_addr(uint64_t addr) {
        // Check if the address is in a reserved range or a kernel address
        return (addr > 0x00000000ull && addr < 0x7FFFFFFFull) || (addr > 0x80000000ull && addr < 0xFFFFC000ull);
    }

    // Searches a given memory region for a pattern of bytes with a wildcard mask
    std::uintptr_t scan_pattern(std::uint8_t* base, const std::size_t size, char* pattern, char* mask) {
        std::size_t pattern_length = strlen(mask);

        for (std::size_t i = 0; i < size - pattern_length; ++i) {
            bool found = true;
            for (std::size_t j = 0; j < pattern_length; ++j) {
                if (mask[j] != '?' && pattern[j] != *(base + i + j)) {
                    found = false;
                    break;
                }
            }

        if (found) {
  	return 0;
}
