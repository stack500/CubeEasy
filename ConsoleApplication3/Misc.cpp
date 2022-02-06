#include <windows.h> //WIN32 API
#include "Misc.h"


Misc::Misc() {                                                   //Default Constructor

}

Misc::~Misc() {                                                  //Deconstructor

}

float Misc::GetDistance3D(vec3_t m_pos, vec3_t en_pos)           //Credits UC
{
    float res = (float)(sqrt(((en_pos.x - m_pos.x) * (en_pos.x - m_pos.x)) + ((en_pos.y - m_pos.y) * (en_pos.y - m_pos.y)) + ((en_pos.z - m_pos.z) * (en_pos.z - m_pos.z))));
    return res;
}


int Misc::getPID(std::string pName) {
        HWND h = FindWindowA(NULL,  pName.c_str());              //MSDN Note: If lpClassName is NULL, it finds any window whose title matches the lpWindowName parameter.
        int pID;
        GetWindowThreadProcessId(h, (LPDWORD)&pID);              //Gets PID from our HWND/Handle and stores it in pID
        return pID;
}








