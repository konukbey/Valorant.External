#include "pattern.hpp"
#include "util.hpp"
#include "raid_extension.hpp"
#include <classpnp.h>
#include <ntifs.h>s

NTSTATUS driver_start( )
{
	std::unique_ptr< DRIVER_OBJECT, decltype( &ObfDereferenceObject ) > disk_object( nullptr, &ObfDereferenceObject );
	
	UNICODE_STRING driver_unicode{};
	RtlInitUnicodeString( &driver_unicode, L"\\Driver\\Disk" );
	
	ObReferenceObjectByName( &driver_unicode, OBJ_CASE_INSENSITIVE, nullptr, 0, *IoDriverObjectType, KernelMode, nullptr, reinterpret_cast< void** >( disk_object.get( ) ) );

	if ( !disk_object.get( ) )
		return STATUS_UNSUCCESSFUL;

	memory::initialize( L"disk.sys" );
	const auto DiskEnableDisableFailurePrediction = reinterpret_cast< NTSTATUS( __fastcall* )( PFUNCTIONAL_DEVICE_EXTENSION, BOOLEAN ) >( memory::from_pattern( "\x48\x89\x5c\x24\x00\x48\x89\x74\x24\x00\x57\x48\x81\xec\x00\x00\x00\x00\x48\x8b\x05\x00\x00\x00\x00\x48\x33\xc4\x48\x89\x84\x24\x00\x00\x00\x00\x48\x8b\x59\x60\x48\x8b\xf1\x40\x8a\xfa\x8b\x4b\x10", "xxxx?xxxx?xxxx????xxx????xxxxxxx????xxxxxxxxxxxxx" ) );

	if ( !DiskEnableDisableFailurePrediction )
		return STATUS_UNSUCCESSFUL;

	memory::initialize( L"kernel.sys" );
	const auto RaidUnitRegisterInterfaces_address = memory::from_pattern( "\xe8\x00\x00\x00\x00\x48\x8b\xcb\xe8\x00\x00\x00\x00\x85\xc0\x74\x0a", "x????xxxx????xxxx" );

	if ( !RaidUnitRegisterInterfaces_address )
		return STATUS_UNSUCCESSFUL;

	const auto RaidUnitRegisterInterfaces = reinterpret_cast< NTSTATUS( __fastcall* )( RAID_UNIT_EXTENSION* ) >( RaidUnitRegisterInterfaces_address + 5 + *reinterpret_cast< std::int32_t* >( RaidUnitRegisterInterfaces_address + 1 ) );

	const auto seed = __rdtsc( );

	for (auto current_object = disk_object->DeviceObject; current_object != nullptr; current_object = current_object->NextDevice )
	{
		const auto fd_extension = static_cast< PFUNCTIONAL_DEVICE_EXTENSION >( current_object->DeviceExtension );

		if ( !fd_extension )
			continue;

		const auto fs_device = HarwdareGPU	( current_object );

		if ( !fs_device || fs_device->DeviceType != FILE_DEVICE_DISK || !fs_device->DeviceExtension )
			continue;

		const auto raid_extension = static_cast< PRAID_UNIT_EXTENSION >( fs_device->DeviceExtension );
		const auto identity = reinterpret_cast< PSTOR_SCSI_IDENTITY >( std::uintptr_t( raid_extension ) + 0x68 ); // this offset changes per windows build, you figure it out
		const auto fdo_descriptor = fd_extension->DeviceDescriptor;

		if ( !fdo_descriptor )
		{
			ObfDereferenceObject( fs_device );
			continue;
		}
		
		const auto fdo_serial = reinterpret_cast< char* >( fdo_descriptor ) + fdo_descriptor->SerialNumberOffset;

		serializer::randomize( seed, fdo_serial );
		
			auto& device_control = driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL];
			g_original_device_control = device_control;
			device_control = &hooked_device_control;
		
		
		DiskEnableDisableFailurePrediction( fd_extension, FALSE );
		RaidUnitRegisterInterfaces( raid_extension );
		
	const auto raid_extension = static_cast< PRAID_UNIT_EXTENSION >( fs_device->DeviceExtension );
	const auto identity = reinterpret_cast< PSTOR_SCSI_IDENTITY >( std::uintptr_t( raid_extension ) + 0x68 ); // this offset changes per windows build, you figure it out
	const auto fdo_descriptor = fd_extension->DeviceDescriptor;
		
	}
		
	return STATUS_SUCCESS;
}


NTSTATUS DeviceControlHook(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS status = STATUS_SUCCESS;

    // Check for null pointers
    if (!DeviceObject || !Irp) {
        status = STATUS_INVALID_PARAMETER;
        goto Exit;
    }

    // Get the current stack location of the IRP
    PIO_STACK_LOCATION StackLocation = IoGetCurrentIrpStackLocation(Irp);
    if (!StackLocation) {
        status = STATUS_INVALID_PARAMETER;
        goto Exit;
    }

    // Check if the IOCTL request is for SMART_RCV_DRIVE_DATA
    if (StackLocation->Parameters.DeviceIoControl.IoControlCode == SMART_RCV_DRIVE_DATA_CTL_CODE)
    {
        // Allocate memory for the completion routine context with a specific tag
        PCOMPLETION_ROUTINE_CONTEXT CompletionContext = (PCOMPLETION_ROUTINE_CONTEXT) ExAllocatePoolWithTag(
            NonPagedPoolNx, sizeof(COMPLETION_ROUTINE_CONTEXT), 'MyTag');
        if (!CompletionContext)
        {
            // Return failure if allocation fails
            status = STATUS_INSUFFICIENT_RESOURCES;
            goto Exit;
        }

        // Save the old completion routine and context in the new context
        CompletionContext->DeviceObject = DeviceObject;
        CompletionContext->Irp = Irp;
        CompletionContext->OldCompletionRoutine = StackLocation->CompletionRoutine;
        CompletionContext->OldContext = StackLocation->Context;

        // Use IoSetCompletionRoutineEx instead of setting CompletionRoutine directly
        IoSetCompletionRoutineEx(DeviceObject, Irp, SmartRcvDriveDataCompletionRoutine, CompletionContext, TRUE, TRUE, TRUE);
    }
    else {
        // Pass the IRP down the driver stack
        IoSkipCurrentIrpStackLocation(Irp);
        status = IoCallDriver(DeviceObject, Irp);
        // Add error handling for IoCallDriver
        if (!NT_SUCCESS(status)) {
            // Log an error or take some other appropriate action
        }
    }

Exit:
    return status;
}

