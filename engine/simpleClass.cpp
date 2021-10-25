#include "simpleClass.h"
#include <iostream>


//////////////
// DLL MAIN //
//////////////

#ifdef _WINDOWS
#include <Windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
 * @param instDLL handle
 * @param reason reason
 * @param _reserved reserved
 * @return true on success, false on failure
 */
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
	// Check use:
   switch (reason)
   {
         ///////////////////////////
         case DLL_PROCESS_ATTACH: //
            break;


         ///////////////////////////
         case DLL_PROCESS_DETACH: //
            break;
   }

   // Done:
   return true;
}
#endif


///////////////////
// BODY OF CLASS //
//////////////////

void LIB_API simpleClass::engineMsg(){
    std::cout << "Sono l'engine 1" << std::endl;
}
