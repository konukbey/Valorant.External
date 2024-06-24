#include "pattern.hpp"
#include <vector>
#include <string>s

void apply_hook()
{
    // Initialize driver object pointer to null
    PDRIVER_OBJECT driver_object = nullptr;

    // Define the driver object name as a constant
    const UNICODE_STRING driver_name = RTL_CONSTANT_STRING(L"\\Driver\\Disk");

    // Attempt to obtain a reference to the driver object
    NTSTATUS status = ObReferenceObjectByName(&driver_name,
                                               OBJ_CASE_INSENSITIVE,
                                               nullptr,
                                               0,
                                               *IoDriverObjectType,
                                               KernelMode,
                                               nullptr,
                                               reinterpret_cast<PVOID*>(&driver_object));

    if (!NT_SUCCESS(status) || driver_object == nullptr)
    {
        // Handle the error and return
        KdPrint(("%s %d : ObReferenceObjectByName returned 0x%08X driver_object: 0x%016X\n",
                  __FUNCTION__,
                  __LINE__,
                  status,
                  driver_object));
        return;
    }

    // Obtain a reference to the original device control function
    PDRIVER_DISPATCH original_device_control = driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL];

    // Replace the original function with the hook function
    driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = hooked_device_control;

    // Store the original function for later use or cleanup
    g_original_device_control = original_device_control;

    // Dereference the driver object
    ObDereferenceObject(driver_object);
}


