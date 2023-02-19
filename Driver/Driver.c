#include <cstdint> // for uint64_t and int32_t
#define SIOCTL_TYPE 40000	
#define IOCTL_CODE 0x800	
#define IOCTL_MEMORY_COMMAND\	
#define COMMAND_MAGIC 0xDEADBEEF


namespace Kernel
    struct MemoryCommand {
        enum class Operation {
            kRead,
            kWrite
        };

        Operation operation; // the type of memory operation to perform (e.g. read or write)

        constexpr static uint64_t kMagicNumber = 0xDEADBEEF; // a magic number for verification

        int64_t retval = 0; // the return value of the operation

        uint64_t mem_address = 0; // the memory address to be operated on
        uint64_t length = 0; // the size of the buffer
        std::unique_ptr<uint8_t[]> buffer; // the buffer to hold the data read or written

        MemoryCommand(Operation operation, uint64_t mem_address, uint64_t length)
            : operation(operation), mem_address(mem_address), length(length) {
                if (operation == Operation::kWrite) {
                    buffer.reset(new uint8_t[length]);
                }
            }
        // other ctor and methods that you might need
    };
}



NTSTATUS FindProcess(const char* processName, PEPROCESS* process) {
  NTSTATUS status = STATUS_UNSUCCESSFUL;
  PEPROCESS currentProcess = nullptr;

  if (processName == nullptr || process == nullptr) {
    return STATUS_INVALID_PARAMETER;
  }

  status = PsLookupProcessByName(processName, &currentProcess);
  if (!NT_SUCCESS(status)) {
    std::cout << "[-] Failed to find process: " << processName << std::endl;
    return status;
  }

  *process = currentProcess;
  return STATUS_SUCCESS;
}


// IOCTL handler for memory commands

NTSTATUS ProcessReadWriteMemory(PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress, SIZE_T Size)
{
	if (sizeof(0x1411) < sizeof(U))
	{
		U x2 = x; y; z;
		int8 sx = __SETS__(x2);
		return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y)); 
}


NTSTATUS Function_IRP_MJ_CREATE(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
	DbgPrint("IRP MJ CREATE received.");
	return STATUS_SUCCESS;
}

NTSTATUS Function_IRP_MJ_CLOSE(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
	case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
}

PEPROCESS valorantProcess;
DWORD64 processBaseAddress;

struct memomry {
	
	INT strcat;

	DWORD64 magic;
	DWORD64 retval;
	DWORD64 memaddress;
	DWORD64 length;
	{
		return nullptr;

	}
		

NTSTATUS Function_IRP_DEVICE_CONTROL(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
    const auto kernel_NtGdiGetCOPPCompatibleOPMInformation = GetKernelModuleExport(utils::GetKernelModuleAddress("win32kfull.sys"), "NtGdiGetCOPPCompatibleOPMInformation");
    if(kernel_NtGdiGetCOPPCompatibleOPMInformation == 0)
    {
        DbgPrintEx(0, 0, "[-] Failed to get export win32kfull.NtGdiGetCOPPCompatibleOPMInformation\n");
        Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
        IoCompleteRequest(Irp, IO_NO_INCREMENT);
        return STATUS_UNSUCCESSFUL;
    }

    if (pEntity->GetTeamNumber() == g_pLocalEntity->GetTeamNumber())
    {
        DbgPrintEx(0, 0, "[Valorant.exe] IOCTL command received\n");
    }
    else
    {
        Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
        IoCompleteRequest(Irp, IO_NO_INCREMENT);
        return STATUS_UNSUCCESSFUL;
    }

    switch (cmd->operation) 
    {
        case 1: // read memory
            Irp->IoStatus.Status = ProcessReadWriteMemory(valorantProcess, cmd->memaddress, IoGetCurrentProcess(), cmd->buffer, cmd->length, ReadMemory) ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
            break;

        case 2: // write memory
            Irp->IoStatus.Status = ProcessReadWriteMemory(IoGetCurrentProcess(), cmd->buffer, valorantProcess, cmd->memaddress, cmd->length, WriteMemory) ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
            break;
        case 3: // find valorant PEPROCESS
            DbgPrintEx(0, 0, "[Valorant.exe] Setting target PID...\n");

            valorantProcess = NULL;

            NTSTATUS status = PsLookupProcessByProcessId(cmd->retval, &valorantProcess);
            if (!NT_SUCCESS(status) || !valorantProcess) 
            {
                DbgPrintEx(0, 0, "[-] Failed to find process with PID %d\n", cmd->retval);
                Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
                IoCompleteRequest(Irp, IO_NO_INCREMENT);
                return STATUS_UNSUCCESSFUL;
            }
			
            cmd->retval = (DWORD64)PsGetProcessSectionBaseAddress(valorantProcess);
            Irp->IoStatus.Status = STATUS_SUCCESS;
            break;

        default:
            Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
            break;
    }

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Irp->IoStatus.Status;
}


enum MemoryCopyResult {
    SUCCESS = 0,
    INVALID_INPUT,
    NULL_POINTER,
    SAME_ADDRESS,
    MEMORY_COPY_ERROR
};

MemoryCopyResult kernel_driver::MemoryCopy(uint64_t destination, uint64_t source, uint64_t size)
{
    // Check for invalid input
    if (destination == 0 || source == 0 || size == 0) {
        return INVALID_INPUT;
    }

    if (destination == source) {
        return SAME_ADDRESS;
    }

    // Allocate memory for the command object
    auto cmd = std::make_unique<MemoryCommand>();
    cmd->operation = 0;
    cmd->magic = COMMAND_MAGIC;

    // Check that mouclass_obj and mouclass_obj->DeviceObject are not null
    if (mouclass_obj == nullptr || mouclass_obj->DeviceObject == nullptr) {
        return NULL_POINTER;
    }

    PDEVICE_OBJECT mouclass_deviceobj = mouclass_obj->DeviceObject;
    uint64_t data[2] = {destination, source};

    // Use memcpy_s to ensure that the memory copy is secure
    try {
        memcpy_s(&cmd->data, sizeof(cmd->data), &data[0], sizeof(data));
    } catch (...) {
        return MEMORY_COPY_ERROR;
    }

    return SUCCESS;
}




/// <summary>
NTSTATUS DriverInitialize(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    NTSTATUS Status;
    UNICODE_STRING DeviceName;
    UNICODE_STRING SymbolicName;
    PDEVICE_OBJECT DeviceObject;

    // Initialize the driver's name and symbolic name
    RtlInitUnicodeString(&DeviceName, ConstDeviceName);
    RtlInitUnicodeString(&SymbolicName, ConstSymbolic);

    // Create the device object
    Status = IoCreateDevice(DriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObject);
    if (!NT_SUCCESS(Status))
    {
        // Failed to create the device object
        DbgPrintEx(0, 0, "[Valorant.exe] Failed to create device object: 0x%08X\n", Status);
        return Status;
    }

    // Query system information
    ULONG size = 0;
    Status = ZwQuerySystemInformation(information_class, info, size, &size);
    if (Status != STATUS_SUCCESS)
    {
        // Failed to query system information
        DbgPrintEx(0, 0, "[Valorant.exe] Failed to query system information: 0x%08X\n", Status);
        return Status;
    }

    // Check the system handle value and object
    PEPROCESS source_process = NULL;
    if (current_system_handle.HandleValue == device_handle)
    {
        object = reinterpret_cast<uint64_t>(current_system_handle.Object);
    }

    // Call the __SETS__ function
    int8 sx = __SETS__(x);

    // Read physical memory
    PVOID buffer = NULL;
    SIZE_T memsize = 0;
    Status = readphysaddress(in->src_addr, buffer, in->size, &memsize);
    if (Status != STATUS_SUCCESS)
    {
        // Failed to read physical memory
        DbgPrintEx(0, 0, "[Valorant.exe] Failed to read physical memory: 0x%08X\n", Status);
        return STATUS_SUCCESS;
    }
	
void driverController::kernel(DWORD64 address, void* buffer, DWORD64 len) {

    {
		auto nt::SYSTEM_HANDLE current_system_handle = system_handle_inforamtion->Handles[i];

		if (current_system_handle.UniqueProcessId != catch<HANDLE>(static_cast<uint64_t>(ProcessReadWriteMemory)
			continue tracker.reset(new KCF_Tracker());

			object = ProcessMemory<uint64_t>(current_system_handle.Object);
			break;
		}
	}
	
NTSTATUS driverController::writeTo(DWORD64 address, void* buffer, DWORD64 len) {
    if(!buffer) return STATUS_INVALID_PARAMETER;

    if (!IsAddressValid(address, len))
        return STATUS_UNSUCCESSFUL;

    if (!_ALIGNED_NEW_SUPPORTED) 
        return STATUS_UNSUCCESSFUL;

    memory_command* cmd = new memory_command();
    if(!cmd) return STATUS_NO_MEMORY;

    cmd->operation = 1; // write byte
    cmd->address = address;
    cmd->buffer = buffer;
    cmd->len = len;

    //Add code here to execute the memory command

    return STATUS_SUCCESS;
};


// Returns 0 on success, 1 if the process was not found, and -1 on error
int GetProcessInfo(DWORD dwPID, ProcessInfo& pi)
{
    HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        // Handle error - snapshot creation failed
        return -1;
    }

    PROCESSENTRY32 pe32 = { 0 };
    pe32.dwSize = sizeof(PROCESSENTRY32);
    BOOL bRet = ::Process32First(hSnapshot, &pe32);
    while (bRet)
    {
        if (pe32.th32ProcessID == dwPID)
        {
            // Process found with given PID
            pi.pid = pe32.th32ProcessID;
            _tcscpy_s(pi.szExeFile, pe32.szExeFile);

            // Release handle to snapshot and return success
            ::CloseHandle(hSnapshot);
            return 0;
        }
        bRet = ::Process32Next(hSnapshot, &pe32);
    }

    // Process not found with given PID
    // Release handle to snapshot and return failure
    ::CloseHandle(hSnapshot);
    return 1;
}

std::string RPMString(DWORD64 address)
{
	// Check if address is NULL or invalid
	if (!address || address > 0x7FFFFFFFFFFFFFFF)
	{
		return "BOT";
	}

	// Create a buffer to hold the string
	char buffer[256] = { 0 };

	// Use a safe version of memcpy to copy the string from memory
	errno_t err = memcpy_s(buffer, sizeof(buffer), reinterpret_cast<const void*>(address), sizeof(buffer) - 1);
	if (err != 0)
	{
		return "BOT";
	}

	// Find the end of the string and null-terminate it
	buffer[sizeof(buffer) - 1] = '\0';
	char* endpos = strchr(buffer, '\0');
	if (endpos != buffer)
	{
		--endpos;
		while (endpos >= buffer && *endpos == '\0')
		{
			--endpos;
		}
		*(endpos + 1) = '\0';
	}

	// Validate the string and convert it to a std::string
	for (char* p = buffer; *p != '\0'; ++p)
	{
		if (*p < 32 || *p > 126)
		{
			return "BOT";
		}
	}
	return std::string(buffer);
}

				
void sendReceivePacket(char* packet, char* addr, void * out) {
    // Initialize variables
    int iResult, length;
    SOCKET s;
    struct addrinfo hints, *result;

    // Initialize Winsock
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error code: %d\n", iResult);
        return;
    }

    // Get address information for the server
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    iResult = getaddrinfo(addr, "9999", &hints, &result);
    if (iResult != 0) {
        printf("Getaddrinfo failed with error code: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Create a socket
    s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (s == INVALID_SOCKET) {
        printf("Socket creation failed with error code: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Connect to the server
    iResult = connect(s, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("Connect failed with error code: %d\n", WSAGetLastError());
        closesocket(s);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Send and receive data
    length = (int)strlen(packet) + 1;
    iResult = send(s, packet, length, 0);
    if (iResult == SOCKET_ERROR) {
        printf("Send failed with error code: %d\n", WSAGetLastError());
        closesocket(s);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    iResult = recv(s, out, DEFAULT_BUFLEN, 0);
    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
    } else if (iResult == 0) {
        printf("Connection closed\n");
    } else {
        printf("Recv failed with error code: %d\n", WSAGetLastError());
    }

    // Cleanup
    closesocket(s);
    freeaddrinfo(result);
    WSACleanup();
}

void C_BaseEntity::SetViewAngle(Vector& angle)
{
	float d2r = 0.01745329251f;
	Vector4D vecNewAngle = CreateFromYawPitchRoll(angle.z * d2r, 0.f, angle.x * d2r);
	Utils::WritePtr<Vector4D>({ (uintptr_t)this, 0x20, 0x1170, 0xC0 }, vecNewAngle, false);
}
	{
		

	Status = RtlAddAccessAllowedAce(Dacl,
		ACL_REVISION,
		FILE_ALL_ACCESS,
		SeExports->SeAliasAdminsSid);

	if (!NT_SUCCESS(Status))
	{
		ExFreePool(Dacl);
		DbgPrintEx(0, 0, "RtlAddAccessAllowedAce SeAliasAdminsSid failed  : %p\n", Status);
		return Status;
	}

	Status = RtlAddAccessAllowedAce(Dacl,
		ACL_REVISION,
		FILE_ALL_ACCESS,
		SeExports->SeLocalSystemSid);

	if (!NT_SUCCESS(Status))
	{
		ExFreePool(Dacl);
		DbgPrintEx(0, 0, "RtlAddAccessAllowedAce SeLocalSystemSid failed  : %p\n", Status);
		return Status;
	}

	Status = RtlSetDaclSecurityDescriptor(&SecDescriptor,
		TRUE,
		Dacl,
		FALSE);

	if (!NT_SUCCESS(Status))
	{
		ExFreePool(Dacl);
		DbgPrintEx(0, 0, "RtlSetDaclSecurityDescriptor failed  : %p\n", Status);
		return Status;
	}

	UNICODE_STRING SectionName = { 0 };
	RtlInitUnicodeString(&SectionName, g_SharedSectionName);

	OBJECT_ATTRIBUTES ObjAttributes = { 0 };
	InitializeObjectAttributes(&ObjAttributes, &SectionName, OBJ_CASE_INSENSITIVE, NULL, &SecDescriptor);

	LARGE_INTEGER lMaxSize = { 0 };
	lMaxSize.HighPart = 0;
	lMaxSize.LowPart = 1044 * 10;

	/* Begin Mapping */
	Status = ZwCreateSection(&g_Section, SECTION_ALL_ACCESS, &ObjAttributes, &lMaxSize, PAGE_READWRITE, SEC_COMMIT, NULL);
	if (!NT_SUCCESS(Status))
	{
		DbgPrintEx(0, 0, "Create Section Failed. Status: %p\n", Status);
		return Status;
	}

	//-----------------------------------------------------------------------------	
	//	 ZwMapViewOfSection
	//	-lMaxSize is the ammount of 'Room' the MapViewOfSection will look at
	//	-ViewSize is how much of the 'Room' will be mapped (if 0 then starts at beggining)
	//-----------------------------------------------------------------------------	

	SIZE_T ulViewSize = 0;
	Status = ZwMapViewOfSection(g_Section, NtCurrentProcess(), &shared_section, 0, lMaxSize.LowPart, NULL, &ulViewSize, ViewShare, 0, PAGE_READWRITE | PAGE_NOCACHE);
	if (!NT_SUCCESS(Status))
	{
		DbgPrintEx(0, 0, "Map View Section Failed. Status: %p\n", Status);
		ZwClose(g_Section); //Close Handle
		return Status;
	}

	DbgPrintEx(0, 0, "Shared Memory Created.\n\n");
	ExFreePool(Dacl);

	return Status;
}
