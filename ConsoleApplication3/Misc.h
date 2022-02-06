#include <string> //for getPID function prototype parameter
#include "Structs.h"


class Misc {
private:

public:
	/*Constructor / Destructor*/
	Misc();
	~Misc();

#ifndef MISC
#define MISC
	/*Function Declarations / Function Prototypes*/
	int getPID(std::string pName);
	float GetDistance3D(vec3_t m_pos, vec3_t en_pos);
#endif

};