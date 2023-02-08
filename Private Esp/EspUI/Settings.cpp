#include "Utils.h"

namespace Settings {
// Menu
bool bMenuEnabled = false;
bool bShutDownEnabled = false;
void* hModule = nullptr;

// Aimbot
bool bAimbotEnabled = false;
int iAimbotMode = 0;
int iFov = 90;
int iBone = 0;

// Visual
bool bLineEnabled = false;
bool bBoxEnabled = false;
int iRank = 300;

// Entity
bool bChamsEnabled = true;
bool bRecoilEnabled = true;
bool bSpreadEnabled = true;
float fSpeed = 175.0f;
float fWepFov = 1.4f;
float fCharFov = 1.4f;
}
