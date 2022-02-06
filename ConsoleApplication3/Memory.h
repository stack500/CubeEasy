#include <string>

class Memory {
	private:
		DWORD procID = 0;				//Initalised to 0 incase constructor can't initalize this upon construction, this will prevent OpenProcess returning an error
	public:
		HANDLE handle;
		//Constructor / Destructor
		Memory(DWORD pid); 
		~Memory(); 

#ifndef MEMORY
#define MEMORY
		//Function Declarations / Function Prototypes
		DWORD writeMemory(DWORD address, int v);
		DWORD getModuleBase(std::string moduleName);

		template <class T>
		T readMemory(DWORD address) {
			T buffer;
			ReadProcessMemory(handle, (LPCVOID)address, &buffer, sizeof(buffer), NULL);
			return buffer;
		}

#endif
};


