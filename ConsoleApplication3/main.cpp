#include <windows.h>     //Win32 API Functions - SetConsoleTitle()
#include <iostream>      //Input/Output
#include <synchapi.h>    //Sleep()
#include <winuser.h>     //GetASyncKeyState()
#include "Hacks.h"       //Hacks class
#include "Memory.h"
#include "Misc.h"

int main()
{
    Misc misc;
    Memory mem(misc.getPID("AssaultCube"));
    SetConsoleTitle(L"CubeEasy - Assault Cube External Cheat v1.2.0.2");

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Stack's AssaultCube v1.2.0.2 External Cheat" << std::endl;
    std::cout << "-------------------------------------------\n" << std::endl;
    std::cout << "F1 - Unlimited Ammo (ALL Weapons)\n" << std::endl;
    std::cout << "F2 - Godmode\n" << std::endl;
    std::cout << "F3 - ESP (Wallhack)\n" << std::endl;
    std::cout << "F4 - No Recoil\n\n" << std::endl;
    std::cout << "F8 - Exit" << std::endl;

    Hacks hacks;                                            //Declare hacks object


    while (!GetAsyncKeyState(VK_F8)) {                      //Main Program Loop


                                                            //User Input Check  -   https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate 

        if (GetAsyncKeyState(VK_F1) & 0x01) {               //Unlimited Ammo
            hacks.unlimitedAmmo();
        }

        else if (GetAsyncKeyState(VK_F2) & 0x01) {          //Godmode
            hacks.godmode();
        }

        else if (GetAsyncKeyState(VK_F3) & 0x01) {          //ESP
            
            hacks.startThread();
        }

        else if (GetAsyncKeyState(VK_F4) & 0x01) {          //No Recoil

            hacks.noRecoil();
        }

        else {
            //do noooooooothing
        }

        Sleep(1);
    }
 }
    





