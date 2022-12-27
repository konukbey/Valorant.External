 uintptr_t DefuseProgress = 0x500;
             uintptr_t CurrentDefuseSection = 0x514;
             uintptr_t TimeRemainingToExplode = 0x4d4;
             uintptr_t BombHasBeenDefused = 0x4DD;
             uintptr_t BombHasExploded = 0x4b0;
            
             uintptr_t uworld_state = 0x9005C00;
             uintptr_t uworld_key = uworld_state + 0x38;
 
             uintptr_t game_instance = 0x1A0; // world + game_instance // TYPE=uintptr_t
             uintptr_t persistent_level = 0x38; // world + persistent_level // TYPE=uintptr_t
 
             uintptr_t local_player_array = 0x40; // game_instance + local_player_array // TYPE=uintptr_t
             uintptr_t local_player_controller = 0x38; // local_player + local_player_controller // TYPE=uintptr_t
             uintptr_t local_player_pawn = 0x460; // local_player_controller + local_player_pawn // TYPE=uintptr_t (=actor)
             uintptr_t control_rotation = 0x440; // local_player_controller + control_rotation // TYPE=Vector3
 
             uintptr_t camera_manager = 0x478; // local_player_controller + camera_manager // TYPE=uintptr_t
             uintptr_t camera_position = 0x1260; // camera_manager + camera_position // TYPE=Vector3
             uintptr_t camera_rotation = 0x126C;  // camera_manager + camera_rotation // TYPE=Vector3
             uintptr_t camera_fov = 0x1278;  // camera_manager + camera_fov // TYPE=float
 
             uintptr_t actor_array = 0xA0; // persistent_level + actor_array // TYPE=uintptr_t
             uintptr_t actor_count = 0xB8; // persistent_level + actor_count // TYPE=int
 
             uintptr_t unique_id = 0x38;  // actor + actor_id // TYPE=uintptr_t
             uintptr_t mesh_component = 0x430; // actor + mesh_component // TYPE=uintptr_t
             uintptr_t last_submit_time = 0x374 + 0x4; // mesh_component + last_submit_time // TYPE=float
             uintptr_t last_render_time = last_submit_time + 0x4; // mesh_component + last_render_time // TYPE=float
             uintptr_t bone_array = 0x5C0; // mesh_component + bone_array // TYPE=uintptr_t
             uintptr_t bone_array_Cached = bone_array + 0x10; // mesh_component + bone_array // TYPE=uintptr_t
             uintptr_t bone_count = bone_array + 0x8; // actor + bone_count // TYPE=uintptr_t
             uintptr_t component_to_world = 0x250; // mesh_component + component_to_world // TYPE=uintptr_t
             uintptr_t root_component = 0x230; // actor + root_component // TYPE=uintptr_t
             uintptr_t RelativeLocation = 0x164;//ok
             uintptr_t root_position = 0x164; // root_component + root_position // TYPE=Vector3
             uintptr_t damage_handler = 0x9a8; // actor/local_player_pawn + damage_handler // TYPE=uintptr_t
             uintptr_t health = 0x1B0; // damage_handler + health // TYPE=float
             uintptr_t dormant = 0x100; // actor + dormant // TYPE=bool
             uintptr_t player_state = 0x3F0; // actor/local_player_pawn + player_state // TYPE=uintptr_t
             uintptr_t team_component = 0x628; // player_state + team_component // TYPE=uintptr_t
             uintptr_t team_id = 0xF8; // team_component + team_id
 
            //inventory
             uintptr_t inventory = 0x948;    
             uintptr_t current_equipable = 0x238;
             uintptr_t ammo_info = 0xfb0;
             uintptr_t max_ammo = 0x120;
             uintptr_t current_ammo = 0x11C;
             uintptr_t ObjID = 0x18;
            //fresnel
             uintptr_t fresnel_intensity = 0x6b8;
            //
             uintptr_t viewangle = 0x170;
 
            //map
             uintptr_t GameState = 0x140;
             uintptr_t    MapLoadModel = 0x140;
             uintptr_t ClientGameInstance = 0x678;
