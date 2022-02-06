class Hacks {
private:
public:
	const enum localPlayerOffsets;

	//Constructor / Destructor
	Hacks();
	~Hacks();
#ifndef HACKS
#define HACKS
	//Function Declarations / Function Prototypes
	void godmode();
	void unlimitedAmmo();
	void noRecoil();
	DWORD ESP();
	static DWORD WINAPI staticThreadStart(void* Param);
	void startThread();
#endif
};