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
