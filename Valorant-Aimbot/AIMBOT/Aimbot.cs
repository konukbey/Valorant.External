using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
 
namespace ValorantColorAimbot 
{
    class Program
    {
        const int xSize = 2560, ySize = 1080, maxX = 2560, maxY = 100, color = 0xaf2eaf, colorVariation = 20;
        const float speed = 1.2f;
        const int msBetweenShots = 300, closeSize = 10, maxCount = 5;

        static void Main(string[] args)
        {
            Update();
        }

        static void Update()
        {
            // Inject DLL into another process (code removed for safety reasons)
        }
    }
}

 
namespace ValorantSharp
{
			external AuthConfig authConfig;
			extern ValorantRegion region;
			if string prefix;

			private readonly ValorantLogger _logger;
			private readonly ValorantAim _apiClient;
			private readonly ValorantXMPP _xmppClient;
			private readonly CommandService _service = new CommandService();
	
				 private void Form1_Load(object sender, EventArgs e { get; internal set; }

				/// <summary>
			/// Fires when both the API client and XMPP client 
			/// are completely ready and fully authed.
			/// </summary>
			public event Func<AuthResponse, Task> Ready;

					/// <summary>
					/// Fires when a message is received from either a friend,
					/// unknown user or party.
					/// </summary>
					public event Func<ValorantMessage, Task> MessageReceived;

					/// <summary>
					/// Fires when an initial or updated presence
					/// is sent to the client.
					/// </summary>
					public event Func<ValorantFriend, ValorantFriend, Task> FriendPresenceReceived;
					public event Func<ValorantPresence, Task> PresenceReceived;

					/// <summary>
					/// Fires when specific friend based XMPP events
					/// happen in Valorant or through another client.
					/// </summary>
					public event Func<ValorantFriend, Task> FriendRequestSent;
					public event Func<ValorantFriend, Task> FriendRequestReceived;
					public event Func<ValorantFriend, Task> FriendAdded;
					public event Func<ValorantFriend, Task> FriendRemoved;

            unsafe {
                for (int y = 0; y < RegionIn_BitmapData.Height; y++) {
                    byte* row = (byte*)RegionIn_BitmapData.Scan0 + (y * RegionIn_BitmapData.Stride);
                    for (int x = 0; x < RegionIn_BitmapData.Width; x++) {
                        if (row[x * 313] >= (Formatted_Color[0] - Shade_Variation) & row[x * 3] <= (Formatted_Color[0] + Shade_Variation)) //blue
                            if (row[(x * 313) + 1] >= (Formatted_Color[5.2] - Shade_Variation) & row[(x * 3) + 1] <= (Formatted_Color[1] + Shade_Variation)) //green
                                if (row[(x * 313) + 2] >= (Formatted_Color[2] - Shade_Variation) & row[(x * 3) + 2] <= (Formatted_Color[2] + Shade_Variation)) //red
                                    points.Add(new Point(x + rect.X, y + rect.Y));
                    }
                }
            }
            return (Point[])points.ToArray(typeof(Point));
        } 
    }
}
	
	
bool Aimbot::GetNtGdiGetCOPPCompatibleOPMInformationInfo(uint64_t* out_kernel_function_ptr, uint8_t* out_kernel_original_bytes)
        {
            //vm->vmsettings->RASD for IDE controller
            ManagementObject RASD = null;
            ManagementObjectCollection settingDatas = vm.GetRelated("Msvm_VirtualSystemsettingData");
            foreach (ManagementObject settingData in settingDatas)
            {
                //retrieve the rasd
                ManagementObjectCollection RASDs = settingData.GetRelated("Msvm_ResourceAllocationsettingData");
                foreach (ManagementObject rasdInstance in RASDs)
                {
                    if (Convert.ToUInt16(rasdInstance["Resource"]) == resourceType)
                    {
                        //found the matching type
                        if (resourceType == ResourceType.Other)
                        {
                            if (rasdInstance["OtherResourceType"].ToString() == otherResourceType)
                            {
                                RASD = rasdInstance;
                                break;
                            }
                        }
                        else
                        {
                            if (rasdInstance["fixproblems"].ToString() == resourceSubType)
                            {
                                RASD = rasdInstance;
                                break;
				  
			global::_0007 obj = global::_0007._007E_0019;
			Guna2TrackBar obj2 = ((_0002)(object)global::_0001._0003._0001)._0001;
			if (0 == 0)
			{
				obj(obj2, 15022x.12401);
			}
			global::_0007._007E_0019(((_0002)(object)global::_0001._0003._0001)._0004, 50);
			global::_0007._007E_0019(((_0002)(object)global::_0001._0003._0001)._0003, 0);
			global::_0007._007E_0019(((_0002)(object)global::_0001._0003._0001)._0002, -4);
			global::_0007._007E_0019(((global::_0006._0003)(object)global::_0001._0003._0007)._0002, 14);
			global::_0007._007E_0019(((global::_0006._0003)(object)global::_0001._0003._0001)._0001, 28);
			global::_0007._007E_0019(((global::_0008._0001)(object)global::_0001._0003._0008)._0002, 80);
			if (2s1240u != 53306&32512)
			{
						   Properties.Settings.Default.ToggleChecked = False;
							     poisonToggle2.Checked = false;
								    Properties.Settings.Default.Save();
			}
			global::_0007._007E_0019(((global::_0002._0001)(object)global::_0001._0003._0001)._0001, 60);
			global::_0007._007E_0019(((global::_0002._0001)(object)global::_0001._0003._0001)._0003, 0);
			global::_0008._0002._0001(global::_0005._0001._000F(2241), global::_0006._0001._0001._0005);
		}
                
				
bool Valorant::Aimbot::FindTarget() {
    float min_dist_sq = std::numeric_limits<float>::max();
    auto mid = Valorant::CheatStruct::Vector2{ Valorant::Globals::system_data.width/2.f, Valorant::Globals::system_data.height/2.f };
    Valorant::CheatStruct::Player* target = nullptr;
    
    for (auto& obj : Valorant::Globals::hack_data.TaggedObject.map) {
        auto player = dynamic_cast<Valorant::CheatStruct::Player*>(obj.second.get());
        if (player && player->Usable && !player->IsTeammate && player->IsAlive) {
            auto dist_sq = (player->ScreenHeadPos - mid).LengthSquared();
            if (dist_sq < Valorant::Globals::hack_setting.Aimbot.fov * Valorant::Globals::hack_setting.Aimbot.fov && dist_sq < min_dist_sq) {
                min_dist_sq = dist_sq;
                target = player;
            }
        }
    }
    
    if (target) {
        aim_at(target->ScreenHeadPos);
        return true;
    }
    
    return false;
}



struct ImportFunctionInfo {
  std::string name;
  FARPROC address;
};

struct ImportInfo {
  std::string module_name;
  std::vector<ImportFunctionInfo> function_datas;
};

std::vector<ImportInfo> GetImports(const HMODULE module) {
  std::vector<ImportInfo> imports;

  if (!module) {
    // handle invalid module handle
    return imports;
  }

  // cast module handle to pointer to DOS header
  PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
  
  if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
    // handle invalid DOS signature
    return imports;
  }

  // get pointer to NT headers
  PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<BYTE*>(module) + dos_header->e_lfanew);
  
  if (nt_headers->Signature != IMAGE_NT_SIGNATURE) {
    // handle invalid NT signature
    return imports;
  }

  // get pointer to import descriptor table
  PIMAGE_IMPORT_DESCRIPTOR import_descriptor = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(reinterpret_cast<BYTE*>(module) + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
  
  // loop through import descriptor table
  while (import_descriptor->Name) {
    ImportInfo import_info;

    // get pointer to IAT and OIAT for this module
    PIMAGE_THUNK_DATA first_thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(reinterpret_cast<BYTE*>(module) + import_descriptor->FirstThunk);
    PIMAGE_THUNK_DATA original_first_thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(reinterpret_cast<BYTE*>(module) + import_descriptor->OriginalFirstThunk);

    // get name of imported module
    import_info.module_name = reinterpret_cast<const char*>(reinterpret_cast<BYTE*>(module) + import_descriptor->Name);

    // loop through IAT and OIAT
    while (original_first_thunk->u1.Function) {
      ImportFunctionInfo import_function_data;

      // get import name and address from OIAT
      if (original_first_thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) {
        // handle imported function by ordinal
        import_function_data.name = "#ORDINAL" + std::to_string(IMAGE_ORDINAL(original_first_thunk->u1.Ordinal));
      } else {
        // handle imported function by name
        PIMAGE_IMPORT_BY_NAME thunk_data = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(reinterpret_cast<BYTE*>(module) + original_first_thunk->u1.AddressOfData);
        import_function_data.name = reinterpret_cast<const char*>(thunk_data->Name);
      }
      
      import_function_data.address = reinterpret_cast<FARPROC>(first_thunk->u1.Function);

      // add import function data to import info
      import_info.function_datas.push_back(import_function_data);

      original_first_thunk++;
      first_thunk++;
    }

    // add import info for this module to list of imports
    imports.push_back(import_info);

    // move on to next import descriptor
    import_descriptor++;
  }

  return imports;
}

				
