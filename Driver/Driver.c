#include <cstdint> // for uint64_t and int32_t
#define SIOCTL_TYPE 40000	
#define IOCTL_CODE 0x800	
#define IOCTL_MEMORY_COMMAND\	
#define COMMAND_MAGIC 0xDEADBEEF


namespace Kernel
{
    struct MemoryCommand
    {
        static const uint64_t kMagicNumber = 0xDEADBEEF;

        std::vector<uint8_t> buffer;
        uint64_t mem_address = 0;
        uint64_t length = 0;
        int64_t retval = 0;
        Operation operation;

        enum class Operation
        {
            kRead,
            kWrite
        };

        MemoryCommand(Operation op, uint64_t addr, uint64_t len)
            : buffer(len), mem_address(addr), length(len), operation(op)
        {
        }

        MemoryCommand(const MemoryCommand& other)
            : buffer(other.buffer), mem_address(other.mem_address), length(other.length),
              retval(other.retval), operation(other.operation)
        {
        }
                else
                {
                    buffer.reset(); // reset the buffer to nullptr
                }
		    }
		    return *this;
		}

		MemoryCommand(MemoryCommand&& other) noexcept // move constructor
		    : operation(other.operation), kMagicNumber(other.kMagicNumber),
		      retval(other.retval), mem_address(other.mem_address), length(other.length),
		      buffer(std::move(other.buffer)) // using std::move for the buffer
		{
		    other.buffer.reset(); // set the original buffer to nullptr
		}

		MemoryCommand& operator=(MemoryCommand&& other) noexcept // move assignment operator
		{
		    if (this != &other)
		    {
			operation = other.operation;
			kMagicNumber = other.kMagicNumber;
			retval = other.retval;
			mem_address = other.mem_address;
			length = other.length;
			buffer = std::move(other.buffer);
			other.buffer.reset(); // set the original buffer to nullptr
		    }
		    return *this;
		}

		~MemoryCommand() // destructor
		{
		    buffer.reset(); // deallocating the buffer
		}

		// accessor methods
		uint64_t get_mem_address() const { return mem_address; }
		uint64_t get_length() const { return length; }
		uint8_t* get_buffer() const { return buffer.get(); } // returning a raw pointer to the buffer
	    };
	}

NTSTATUS FindProcess(const char* processName, PEPROCESS* process) {
    if (processName == nullptr || process == nullptr) {
        return STATUS_INVALID_PARAMETER;
    }

    UNICODE_STRING uniProcessName;
    RtlInitUnicodeString(&uniProcessName, L"");

    // Convert the input ANSI string to a Unicode string
    ANSI_STRING ansiProcessName;
    RtlInitAnsiString(&ansiProcessName, processName);
    NTSTATUS status = RtlAnsiStringToUnicodeString(&uniProcessName, &ansiProcessName, TRUE);

    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] Failed to convert process name to Unicode string: %s\n", processName);
        return status;
    }

    // Look up the process by name
    PEPROCESS currentProcess = nullptr;
    status = PsLookupProcessByProcessName(&uniProcessName, &currentProcess);

    // Free the memory allocated for the Unicode string
    RtlFreeUnicodeString(&uniProcessName);

    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] Failed to find process: %s\n", processName);
        return status;
    }

    // Store a pointer to the PEPROCESS structure in the output parameter
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

struct memory {
    int capacity, size;
    char *data;

    memory(int capacity) : capacity(capacity), size(0), data(new char[capacity]) {}

    ~memory() { delete[] data; }

    bool strcat(const char *str) {
        int len = strlen(str);
        if (size + len >= capacity) return false;
        strcpy(data + size, str), size += len;
        return true;
    }

    char *strstr(const char *str) { return std::strstr(data, str); }
};


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

// Define an enum to represent the result of the function
enum class MemoryCopyResult {
    SUCCESS,
    INVALID_INPUT,
    SAME_ADDRESS,
    NULL_POINTER,
    MEMORY_COPY_ERROR
};

MemoryCopyResult kernel_driver::MemoryCopy(uint64_t destination, uint64_t source, uint64_t size)
{
    // Check for invalid input
    if (destination == 0 || source == 0 || size == 0) {
        return MemoryCopyResult::INVALID_INPUT;
    }

    if (destination == source) {
        return MemoryCopyResult::SAME_ADDRESS;
    }

    // Allocate memory for the command object
    std::unique_ptr<MemoryCommand> cmd(new MemoryCommand());
    cmd->operation = 0;
    cmd->magic = COMMAND_MAGIC;

    // Check that mouclass_obj and mouclass_obj->DeviceObject are not null
    if (mouclass_obj == nullptr || mouclass_obj->DeviceObject == nullptr) {
        return MemoryCopyResult::NULL_POINTER;
    }

    // Ensure that the size of the data block to be copied is not larger than the size of the command buffer
    if (size > sizeof(cmd->data)) {
        return MemoryCopyResult::INVALID_INPUT;
    }

    // Copy the destination and source addresses to the command buffer
    uint64_t data[2] = {destination, source};
    errno_t err = memcpy_s(&cmd->data, sizeof(cmd->data), &data[0], size);
    if (err != 0) {
        return MemoryCopyResult::MEMORY_COPY_ERROR;
    }

    // Use the command buffer to initiate the memory copy operation
    PDEVICE_OBJECT mouclass_deviceobj = mouclass_obj->DeviceObject;
    // ...

    return MemoryCopyResult::SUCCESS;
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
    if (!buffer) {
        return STATUS_INVALID_PARAMETER;
    }

    if (!IsAddressValid(address, len)) {
        return STATUS_ACCESS_VIOLATION;
    }

    if (!_ALIGNED_NEW_SUPPORTED) {
        return STATUS_NOT_SUPPORTED;
    }

    if (!IsAddressWritable(address)) {
        return STATUS_ACCESS_DENIED;
    }

    PVOID mappedAddress = MapAddress(address);
    if (!mappedAddress) {
        return STATUS_ACCESS_VIOLATION;
    }

    memcpy(mappedAddress, buffer, len);
    UnmapAddress(mappedAddress);

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

std::string RPMString(const void* address, size_t maxLength)
{
    // Check if address is NULL
    if (address == nullptr)
    {
        return "";
    }

    // Create a buffer to hold the string
    std::vector<char> buffer(maxLength + 1, 0);

    // Copy the string from memory into the buffer
    memcpy(&buffer[0], address, maxLength);

    // Find the end of the string and null-terminate it
    size_t length = strnlen_s(buffer.data(), maxLength);
    buffer[length] = '\0';

    // Validate the string and convert it to a std::string
    for (size_t i = 0; i < length; ++i)
    {
        char c = buffer[i];
        if (c < 32 || c > 126)
        {
            return "";
        }
    }

    return std::string(buffer.data());
}

				
int sendReceivePacket(const char* packet, const char* addr, void* out, size_t outSize) {
    // Initialize variables
    int iResult, length;
    SOCKET s = INVALID_SOCKET;
    struct addrinfo hints = {0}, *result = NULL;

    // Initialize Winsock
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error code: %d\n", iResult);
        return iResult;
    }

    // Get address information for the server
    hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Use TCP
    hints.ai_protocol = IPPROTO_TCP; // Use TCP

    iResult = getaddrinfo(addr, "9999", &hints, &result);
    if (iResult != 0) {
        fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(iResult));
        WSACleanup();
        return iResult;
    }

    // Create socket and connect to the server
    s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (s == INVALID_SOCKET) {
        fprintf(stderr, "socket creation failed with error code: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return WSAGetLastError();
    }

    iResult = connect(s, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        fprintf(stderr, "connect failed with error code: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(s);
        WSACleanup();
        return WSAGetLastError();
    }

    // Send the packet to the server
    length = (int)strlen(packet);
    iResult = send(s, packet, length, 0);
    if (iResult == SOCKET_ERROR) {
        fprintf(stderr, "send failed with error code: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(s);
        WSACleanup();
        return WSAGetLastError();
    }

    // Receive response from the server
    iResult = recv(s, (char*)out, outSize, 0);
    if (iResult == SOCKET_ERROR) {
        fprintf(stderr, "recv failed with error code: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(s);
        WSACleanup();
        return WSAGetLastError();
    }

    // Cleanup
    freeaddrinfo(result);
    closesocket(s);
    WSACleanup();
    return iResult;
}

// Free the memory allocated by getaddrinfo
freeaddrinfo(result);


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

int iResult = recv(s, out, DEFAULT_BUFLEN, 0);
if (iResult > 0) printf("Bytes received: %d\n", iResult);
else if (iResult == 0) printf("Connection closed\n");
else printf("Recv failed with error code: %d\n", WSAGetLastError());

closesocket(s);
freeaddrinfo(result);
WSACleanup();


void C_BaseEntity::SetViewAngle(const Vector& angleInDegrees)
{
    const float degreesToRadians = 0.01745329251f;
    const Vector4D viewAngleQuaternionRotation = CreateQuaternionFromAngles(angleInDegrees.z * degreesToRadians, 0.f, angleInDegrees.x * degreesToRadians);
    const uintptr_t viewAngleAddress = reinterpret_cast<uintptr_t>(this) + VIEW_ANGLE_OFFSET;
    if (!Utils::WritePtr<Vector4D>(viewAngleAddress, viewAngleQuaternionRotation, false))
    {
        // Handle error: failed to write view angle to memory
    }
}
