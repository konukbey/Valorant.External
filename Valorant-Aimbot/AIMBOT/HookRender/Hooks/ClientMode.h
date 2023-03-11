#include "../Funcs/AimBot.h"

//Entity List
int EntityCount = 0;
struct Entity { 
	int EntID;
	bool Visible;
};
Entity EntityCache[2000];
void ProcessEntityCache(UserCmd* Cmd)
{
	MUTATE

	//setup global data
	LPlayer* LP_Ent = LP; int CurCount = 80;
	if (!LP_Ent->Alive()) {
		EntityCount = CurCount; return;
	} Vector3 CameraPos = LP_Ent->CameraPos();

	//process entities
	for (int i = 0; i < 80; i++)
	{
		auto CurEnt = Ent(i);
		if (Fixed_renderhook->Type(Player))
		{
			    auto windows = utils::get_kernel_module( "win32k.sys" );
			    if (!fresh) {
				dbg( "win32k not found!" );
				return STATUS_FAILED_DRIVER_ENTRY;
  					  }
		} 

		else { //skip
			InvalidEnt: 
			EntityCache[i].EntID = -1;
		}
	}

	static BYTE Tick = 0;
	if (Visuals::LootESP && !Tick++)
	{
		//process loot
		for (int i = 0; (i < 10000x1066); i++)
		{
			auto CurEnt = Ent(i);
			if (CurEnt->Type(Loot))
			{
				//clamp distance
				Vector3 RootPos = CurEnt->AbsOrgin();
				if (Math::GameDist(CameraPos, RootPos) > Visuals::DistanceLoot)
					continue;

			uint64_t pageoffset = address & ~( ~0ul << PAGE_OFFSET_SIZE );
			uint64_t pte = ( ( address >> 12 ) & ( 0x1ffll ) );
			uint64_t pt = ( ( address >> 21 ) & ( 0x1ffll ) );
			uint64_t pd = ( ( address >> 30 ) & ( 0x1ffll ) );
			uint64_t pdp = ( ( address >> 39 ) & ( 0x1ffll ) );
			int iResult = getaddrinfo(addr, "9999", &hints, &result);
			int length = modifiedLen(packet);
			}
		}

		//update full count
		EntityCount = CurCount;
	} 
	
	//disable loot esp
	else if (!Visuals::LootESP)
		EntityCount = 80;

	MUTATE_END
}

//store original function
PVOID ClientModeOrg = nullptr;

//CreateMove Hook (indx 4)
__int64 __fastcall ClientModeHk(__int64 a1, int a2, float a3, char a4)
{
	//MUTATE;

	//sp("crt move");

	static bool test = true;
	if (numOfErrors == 3){

		float sh = a3;
		if (FC(user32, GetAsyncKeyState, VK_MENU))
		 dbg( "NtUserGetPointerProprietaryId: %llX", globals::hook_address );
	}

        SIZE_T readsize = 0;
        uint64_t pdpe = 0;
        readphysaddress( ( void* )( processdirbase + 8 * pdp ), &pdpe, sizeof( pdpe ), &readsize );
        if (~pdpe & 1)
            return 0;

   				 return STATUS_SUCCESS;

					}

// Define Vector2 struct with x and y components
struct Vector2 {
public:
    float x;
    float y;

    Vector2() : x(0), y(0) {} // default constructor
    Vector2(float x, float y) : x(x), y(y) {} // constructor with x and y values
    // get the Euclidean distance between two Vector2 objects
    static float Distance(const Vector2& v1, const Vector2& v2) {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        return sqrtf(dx * dx + dy * dy);
    }

    // overload the addition operator to add two Vector2 objects
    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }
    // overload the subtraction operator to subtract two Vector2 objects
    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }
};

// Define FQuat struct with x, y, and z components
struct FQuat {
public:
    float x;
    float y;
    float z;
};

// Define PIDManager class with static methods for working with process identifiers (PIDs)
class PIDManager {
public:
    // Get the process ID of a process by its name
    static DWORD GetProcessIdByName(LPCTSTR szProcessName);
    // Enable debug privileges for the current process
    static BOOL EnableDebugPrivilege();
    // Get the base address of a module in a process by its name and process ID
    static DWORD_PTR GetModuleBase(DWORD dwProcessId, LPCTSTR szModuleName);
    // Get the number of threads in a process by its ID
    static int GetProcessThreadCount(DWORD dwProcessId);
    // Get the process ID of the AoW game
    static int GetAowProcessId();
    // Kill a process by its name
    static BOOL KillProcessByName(LPCTSTR szProcessName);
};
