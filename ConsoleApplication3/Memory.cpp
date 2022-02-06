#include <windows.h>	//Win32 API Functions - ReadProcessMemory/WriteProcessMemory
#include <TlHelp32.h>	//GetModule()
#include <iostream>
#include "Memory.h"		//headerfile



//Implementation / Definitions

Memory::Memory(DWORD pID) {																//Constructor
	procID = pID;
	handle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_OPERATION, FALSE, procID);		//Initializing our handle member and using Win32 OpenProcess to open handle
}

Memory::~Memory() {																		//Destructor
	CloseHandle(handle);																//Close handle upon deconstruction of object to prevent memory leaks
}


DWORD Memory::writeMemory(DWORD address, int v) { 
	WriteProcessMemory(handle, (LPVOID)address, &v, sizeof(v), NULL);
	return NULL;
}

DWORD Memory::getModuleBase(std::string moduleName) {
	//HMODULE test = GetModuleHandleA("ac_client.exe");				//Im retarded, I realizd this can only be used internally
	//TODO - Write this function using tlhelp32						//only way to get module base externally (to my understanding)
	
	return NULL;
}









