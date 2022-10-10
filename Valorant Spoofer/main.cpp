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

	memory::initialize( L"storport.sys" );
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

		const auto fs_device = IoGetDeviceAttachmentBaseRef( current_object );

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

		identity->SerialNumber.Length = static_cast< USHORT >( std::strlen( fdo_serial ) );
		memset( identity->SerialNumber.Buffer, 0, identity->SerialNumber.Length );
		memcpy( identity->SerialNumber.Buffer, fdo_serial, identity->SerialNumber.Length );

		DiskEnableDisableFailurePrediction( fd_extension, FALSE );
		RaidUnitRegisterInterfaces( raid_extension );
		
		const auto raid_extension = static_cast< PRAID_UNIT_EXTENSION >( fs_device->DeviceExtension );
		const auto identity = reinterpret_cast< PSTOR_SCSI_IDENTITY >( std::uintptr_t( raid_extension ) + 0x68 ); // this offset changes per windows build, you figure it out
		const auto fdo_descriptor = fd_extension->DeviceDescriptor;
	}
		
	return STATUS_SUCCESS;
}

NTSTATUS DeviceControlHook ( const PDEVICE_OBJECT deviceObject , const PIRP irp ) {
	const auto stackLocation = IoGetCurrentIrpStackLocation ( irp );
	switch ( stackLocation->Parameters.DeviceIoControl.IoControlCode ) {
	case SMART_RCV_DRIVE_DATA: {
		const auto context = reinterpret_cast< HWID::CompletionRoutineInfo* >( ExAllocatePool ( NonPagedPool ,
			sizeof ( HWID::CompletionRoutineInfo ) ) );
		context->oldRoutine = stackLocation->CompletionRoutine;
		context->oldContext = stackLocation->Context;
		stackLocation->CompletionRoutine = reinterpret_cast< PIO_COMPLETION_ROUTINE >( smartRcvDriveDataCompletion );
		stackLocation->Context = context;
		break;
	}
	}

	return originalDeviceControl ( deviceObject , irp );
}

NTSTATUS HWID::ClearPropertyDriveSerials ( ) {
	// dont null the serials but randomise instead
	// returns STATUS_SUCCESS if the nulling off the property drive serials  was successful. 
	//  nulls it by using memset

	//Improve:
	//-Dont NULL the serials, but randomise.

	std::uint8_t serialNumberOffset {};
	{ // Find the serial number offset
		std::uintptr_t storportBase {};
		std::size_t storportSize {};
		Nt::findKernelModuleByName ( "storport.sys" , &storportBase , &storportSize );  // grabs the storport.sys base 

		if ( !storportBase ) { return STATUS_INVALID_ADDRESS; }


		// The code we're looking for is in the page section
		std::uintptr_t storportPage {};
		std::size_t storportPageSize {};
		Nt::findModuleSection ( storportBase , "PAGE" , &storportPage , &storportPageSize );

		if ( !storportPage ) { return STATUS_INVALID_ADDRESS; }


		const auto serialNumberFunc = SigScan::scanPattern ( reinterpret_cast< std::uint8_t* >( storportPage ) , storportPageSize ,
			"\x66\x41\x3B\xF8\x72\xFF\x48\x8B\x53" , "xxxxx?xxx" );  // scans for the function which contains the serialnumbers

		if ( !serialNumberFunc ) { return STATUS_INVALID_ADDRESS; }


		serialNumberOffset = *reinterpret_cast< std::uint8_t* >( serialNumberFunc + 0x9 );
		if ( !serialNumberOffset ) { return STATUS_INVALID_ADDRESS; }

	}
	
	
	NTSTATUS Nt::findModuleExportByName ( const std::uintptr_t imageBase , const char* exportName , std::uintptr_t* functionPointer ) {
	if ( !imageBase )
		return STATUS_INVALID_PARAMETER_1;

	if ( reinterpret_cast< PIMAGE_DOS_HEADER >( imageBase )->e_magic != 0x5A4D )
		return STATUS_INVALID_IMAGE_NOT_MZ;

	const auto ntHeader = reinterpret_cast< PIMAGE_NT_HEADERS64 >( imageBase + reinterpret_cast< PIMAGE_DOS_HEADER >( imageBase )->e_lfanew );
	const auto exportDirectory = reinterpret_cast< PIMAGE_EXPORT_DIRECTORY >( imageBase + ntHeader->OptionalHeader.DataDirectory [ 0 ].VirtualAddress );
	if ( !exportDirectory )
		STATUS_INVALID_IMAGE_FORMAT;

	const auto exportedFunctions = reinterpret_cast< std::uint32_t* >( imageBase + exportDirectory->AddressOfFunctions );
	const auto exportedNames = reinterpret_cast< std::uint32_t* >( imageBase + exportDirectory->AddressOfNames );
	const auto exportedNameOrdinals = reinterpret_cast< std::uint16_t* >( imageBase + exportDirectory->AddressOfNameOrdinals );

	for ( std::size_t i {}; i < exportDirectory->NumberOfNames; ++i ) {
		const auto functionName = reinterpret_cast< const char* >( imageBase + exportedNames [ i ] );
		if ( !strcmp ( exportName , functionName ) ) {
			*functionPointer = imageBase + exportedFunctions [ exportedNameOrdinals [ i ] ];
			return STATUS_SUCCESS;
		}
	}

		
		void CleanCaches() {
	system(_xor_("reg delete HKLM\\SOFTWARE\\WOW6432Node\\EasyAntiCheat /f").c_str());
}
		
void Spoofing::ChangeRegEdit() {
	std::string value = newUUID();
	//std::string value2 = newUUID();
	std::thread([&] {
		std::string cmdtoexec = encyption.GetMachineGuidRegEdit().c_str();
		cmdtoexec += value;
		//std::string cmdtoexec2 = encyption.GetProfileGuidRegEdit().c_str();
		//cmdtoexec2 += value2;
		system(cmdtoexec.c_str());
		//system(cmdtoexec2.c_str()); crashing
	}).detach();
	std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m GUID changed to: " << value << std::endl;
	//std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m Profile GUID changed to: " << value2 << std::endl;
}
