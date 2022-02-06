#include <windows.h>		//WIN32 API
#include "Hacks.h"			//Header files
#include "Structs.h"		
#include "Memory.h"			
#include "Misc.h"			
#include "Draw.h"			



Misc m;															//Declare Misc Object
int pID = m.getPID("AssaultCube");								
Memory mem(pID);												//Declare Memory Object


/*Yes it's hardcoded, will write a function in the misc class to get module later*/
const DWORD g_localPlayerBase = 0x509B74;
const DWORD g_entityBase = 0x50F4F8;
const DWORD g_moduleBase = 0x00400000;

COLORREF g_enemyColor;
const HBRUSH g_hBrushEnemy = CreateSolidBrush(RGB(37, 190, 64));

const enum localPlayerOffsets {
	healthOff = 0xF8, //4 Bytes (int)
	armour = 0xFC, //4 Bytes (int)
	mosX = 0x40, //4 Bytes (float)
	moxY = 0x44, //4 Bytes (float)
	ARMagAmmo = 0x150, //4 Bytes (int)
	ARResAmmo = 0x128, //4 Bytes (int)
	pistolMag = 0x13C, //4 Bytes (int)
	pistolRes = 0x114, //4 Bytes (int)
	viewMatrix = 0x501AE8,
	POS_X_NORMAL = 0x34,
    POS_Y_NORMAL = 0x38,
    POS_Z_NORMAL = 0x3C,
};


Hacks::Hacks() {				//Default Constructor

}


Hacks::~Hacks() {				//Destructor
	
} 




void Hacks::godmode() {
	mem.writeMemory((g_localPlayerBase + healthOff), 6969);
	const BYTE newBytes[] = {0x90, 0x90, 0x90}; //patch with three 0x90 0x90 bytes (nop)
	WriteProcessMemory(mem.handle, (LPVOID)(g_moduleBase + 0x29D1F), &newBytes, sizeof(newBytes), 0); //health dec function 
}

void Hacks::unlimitedAmmo() { //ADD GRENADES LATER
	const BYTE newBytes[] = { 0x90, 0x90 }; //patch with two 0x90 0x90 bytes (nop) (main weapon)
	const BYTE oldBytes[] = { 0xFF, 0x0E };
	int buffer = 6969;
	WriteProcessMemory(mem.handle, (LPVOID)(g_localPlayerBase + ARMagAmmo), &buffer, sizeof(buffer), 0);
}

void Hacks::noRecoil() {
	const BYTE oldBytes[] = { 0x50, 0x8D, 0x4C, 0x24, 0x1C, 0x51, 0x8B, 0xCE, 0xFF, 0xD2 };
	const BYTE newBytes[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	WriteProcessMemory(mem.handle, (LPVOID)(g_moduleBase + 0x63786), &newBytes, sizeof(newBytes), 0);
}



DWORD Hacks::ESP() {
	
	//Variable Declarations

	HWND TargetWnd = FindWindow(0, L"AssaultCube");
	HDC HDC_Desktop = GetDC(TargetWnd);											//Getting (X - too stoned) for Draw object initialization
	Draw d(HDC_Desktop, TargetWnd);												//Draw Object Declared																	
	enemy en[64];																//Enemy Array
	float matrix[16];															//View Matrix
	vec3_t screen, myPos;																//To pass for drawESP()
	DWORD newLocalPlayer = mem.readMemory<DWORD>(g_moduleBase + 0x109B74);		//test later and see if same as g_localPlayer

	while (true) {
		int i = 1;																	//loop counter
		//Set Player Position
		myPos.x = mem.readMemory<float>(g_localPlayerBase + POS_X_NORMAL);
		myPos.y = mem.readMemory<float>(g_localPlayerBase + POS_Y_NORMAL);
		myPos.z = mem.readMemory<float>(g_localPlayerBase + POS_Z_NORMAL);

		//Declare & Initialize Total Players
		int totalPlayers = mem.readMemory<int>(0x50F500);

		//Declare & Initialize entityList
		DWORD entityList = mem.readMemory<DWORD>(g_moduleBase + 0x10F4F8);			

		//Read viewMatrix
		ReadProcessMemory(mem.handle, (PBYTE*)0x501AE8, &matrix, sizeof(matrix), 0);

		//Loop Iteration through entityBase/List
		for (DWORD x = 0x4; x <= (0x4 * (totalPlayers - 1)); x += 0x4) {
			i++; //loop count increase by 1


			en[i].enemyBase = mem.readMemory<DWORD>(entityList + x); 
			en[i].pos.x = mem.readMemory<float>(en[i].enemyBase + POS_X_NORMAL);
			en[i].pos.y = mem.readMemory<float>(en[i].enemyBase + POS_Y_NORMAL);
			en[i].pos.z = mem.readMemory<float>(en[i].enemyBase + POS_Z_NORMAL);

			if (d.WorldToScreen(en[i].pos, screen, matrix, 800, 600)) {		
			
				d.DrawESP(screen.x, screen.y, m.GetDistance3D(myPos, en[i].pos), g_hBrushEnemy);
			}

			else
			{
				//do nothing
			}
		}	
	}

	return NULL;
}




DWORD WINAPI Hacks::staticThreadStart(void* Param) {
	Hacks* Test = (Hacks*)Param;
	return Test->ESP();
}



void Hacks::startThread() {
	DWORD tID;
	CreateThread(NULL, 0, staticThreadStart, (void*) this, 0, &tID);
}










	