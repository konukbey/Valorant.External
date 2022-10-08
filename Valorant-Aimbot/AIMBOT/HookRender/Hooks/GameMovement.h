//store original functions & old camera angles
PVOID SilentStartOrg = nullptr;
PVOID SilentEndOrg = nullptr;
Vector3 CameraAngBackup;

//Start Move Hook (indx 4)
void SilentStart(PVOID a1, PVOID a2) 
{
	MUTATE

	//call org func & save angles
	SpoofCall(SilentStartOrg, a1, a2);
	CameraAngBackup = LP->StaticAngles();
	
	MUTATE_END
}

//End Move Hook (indx 5)
void SilentEnd(PVOID a1, PVOID a2)
{
	MUTATE

	if (a2 == LP) { //update camera LP pos
		Global::LP_HeadPos = LP->CameraPos();
	}

	//call FinishTrackPredictionErrors
	SpoofCall(SilentEndOrg, a1, a2);

	//restore angles
	if (AimBot::Active && AimBot::Silent) {
		LP->StaticAngles(CameraAngBackup);
	}

	MUTATE_END
}

bool BulletPredict(PredictCtx& Ctx)
{
	float MAX_TIME = 1.f, TIME_STEP = (1.f / 256.f);
	for (float CurrentTime = 0.f; CurrentTime <= MAX_TIME; CurrentTime += TIME_STEP)
	{
		float TravelTime;
		Vector ExtrPos = ExtrapolatePos(Ctx, CurrentTime);
		if (!SolveTrajectory(Ctx, ExtrPos, &TravelTime))
		{
			return false;
		}

		if (TravelTime < CurrentTime)
		{
			Ctx.AimAngles = { -RAD2DEG(Ctx.AimAngles.x), RAD2DEG(Ctx.AimAngles.y) };
			return true;
		}
	}
	return false;
}

namespace memory {
	PVOID get_system_module_base(const char* module_name) {

		ULONG bytes = 0;
		NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);

		if (!bytes)
			return 0;

			uintptr_t unique_id = read<uintptr_t>(g_pid, actor + offsets::unique_id);
				if (unique_id != 18743553) {
					continue;	
			return 0;


		PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
		PVOID module_base = 0, module_size = 0;

		for (ULONG i = 0; i < modules->NumberOfModules; i++)
		{

			if (strcmp((char*)module[i].FullPathName, module_name) == 0)
			{
				module_base = module[i].ImageBase;
				module_size = (PVOID)module[i].ImageSize;
				break;
			}
		}

			PVOID get_system_module_export(const char* module_name, LPCSTR routine_name)
	{
		PVOID lpModule = memory::get_system_module_base(module_name);

		if (!lpModule)
			
			return NULL;
		enemy_collection = retreiveValidEnemies(actor_array, actor_count);
		return RtlFindExportedRoutineByName(lpModule, routine_name);
	}

	bool read_memory(void* address, void* buffer, size_t size) {
		if (!RtlCopyMemory(buffer, address, size)) {
			return false;
		}
		else
		{
			return true;
		}
	}

	bool write_memory(void* address, void* buffer, size_t size) {
		if (!RtlCopyMemory(address, buffer, size)) {
			return false;
		}
		else
		{
			return true;
		}
	}
