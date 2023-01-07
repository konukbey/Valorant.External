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
NTSTATUS DeviceControlHook(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    // Get the current stack location of the IRP
    PIO_STACK_LOCATION stackLocation = IoGetCurrentIrpStackLocation(irp);

    // Check the IO control code
    switch (stackLocation->Parameters.DeviceIoControl.IoControlCode)
    {
        case SMART_RCV_DRIVE_DATA:
        {
            // Allocate memory for the completion routine context
            auto context = reinterpret_cast<HWID::CompletionRoutineInfo*>(ExAllocatePoolWithTag(NonPagedPool,
                sizeof(HWID::CompletionRoutineInfo), TAG_HWID));
            if (!context)
            {
                // Return failure if allocation fails
                irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
                irp->IoStatus.Information = 0;
                IoCompleteRequest(irp, IO_NO_INCREMENT);
                return STATUS_INSUFFICIENT_RESOURCES;
            }

            // Save the old completion routine and context in the new context
            context->oldRoutine = stackLocation->CompletionRoutine;
            context->oldContext = stackLocation->Context;

            // Set the new completion routine and context
            stackLocation->CompletionRoutine = reinterpret_cast<PIO_COMPLETION_ROUTINE>(smartRcvDriveDataCompletion);
            stackLocation->Context = context;
            break;
        }
    }

    // Call the original DeviceControl function
    return originalDeviceControl(deviceObject, irp);
}


void Spoofing::GetFiveM() {
	std::cout << "\x1B[31m[\033[0m\x1B[33m!\033[0m\x1B[31m]\033[0m Please, select FiveM application data folder! " << std::endl;
	std::string folderpath;
	GetFolder(folderpath, "Select FiveM application data folder!");
	std::string cache = folderpath;
	cache += "\\cache";
	std::string ros_profilespath = folderpath;
	ros_profilespath += "\\cache\\game\\ros_profiles";
	std::string priv = folderpath;
	priv += "\\cache\\priv";
	std::string asifive = folderpath;
	asifive += "\\asi-five.dll";
	uintmax_t delfiles = 0;

	if (exists_test3(cache)) {
		delfiles += std::filesystem::remove_all(ros_profilespath);
		delfiles += std::filesystem::remove_all(priv);
		delfiles += std::filesystem::remove_all(asifive);
		std::cout << "\x1B[31m[\033[0m\x1B[33m!\033[0m\x1B[31m]\033[0m Removing FiveM game files... (to initialize update) " << std::endl;
		std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m Deleted \x1B[96mFiveM\033[0m " << delfiles << " files or directories\n";
		if (delfiles <= 0) {
			std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m Removed 0 or less \x1B[96mFiveM\033[0m files, don't you think it's weird?" << std::endl;
		}
	}
	else {
		std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m You are missing cache file in \x1B[96mFiveM\033[0m application folder, don't you think it's weird? | SKIPPING" << std::endl;
	}
		
 void ChangeRegEdit() {
    // Generate new UUIDs.
    std::string machine_guid = newUUID();
    std::string profile_guid = newUUID();

    // Create a lambda function to execute the commands in a separate thread.
    // Capture the local variables by reference to make them available to the lambda.
    std::thread([&] {
      // Construct the commands to be executed.
      std::string cmd_machine_guid = encyption_.GetMachineGuidRegEdit() + machine_guid;
      std::string cmd_profile_guid = encyption_.GetProfileGuidRegEdit() + profile_guid;

      // Execute the commands.
      std::system(cmd_machine_guid.c_str());
      std::system(cmd_profile_guid.c_str());
    }).detach();

    // Print the new values of the keys.
    std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m GUID changed to: " << machine_guid << std::endl;
    std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m Profile GUID changed to: " << profile_guid << std::endl;
  }

private:
  Encyption encyption_;
};
Some of the changes I made include:

Including the necessary headers and forward-declaring the newUUID() function and the Encyption class and its member functions.
Using the std::system() function instead of the system() function.
Using a lambda function to execute the commands in a separate thread instead of using the std::thread constructor directly. This allows the thread to capture local variables by reference, which is necessary to make the machine_guid and

