/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/


#include "../include/pron.h"

#ifdef _MANAGED
  #pragma managed(push, off)
#endif


#if defined(_WIN32) || defined(USES_DLLMAIN)

extern "C" BOOL APIENTRY DllMain(
  HMODULE hModule,
  DWORD ul_reason_for_call,
  LPVOID lpReserved);

extern "C" BOOL APIENTRY DllMain(
  HMODULE hModule,
  DWORD ul_reason_for_call,
  LPVOID lpReserved)
{

  if (ul_reason_for_call == DLL_PROCESS_ATTACH)
  {
    // Can initialize here.
  }
  else if (ul_reason_for_call == DLL_PROCESS_DETACH)
  {
    // Can release and close here.
  }

  UNUSED(hModule);
  UNUSED(lpReserved);

  return 1;
}

#elif (defined(__IPHONE_OS_VERSION_MAX_ALLOWED) || defined(__MAC_OS_X_VERSION_MAX_ALLOWED))

void PronInitialize(), PronFinalize();

void PronInitialize(void) 
{
  // Can initialize here.
}


void PronFinalize(void) 
{
  // Can release and close here.
}

#elif defined(USES_CONSTRUCTOR)

static void __attribute__ ((constructor)) libInit(void)
{
  // Can initialize here.
}


static void __attribute__ ((destructor)) libEnd(void)
{
  // Can release and close here.
}

#endif

#ifdef _MANAGED
  #pragma managed(pop)
#endif

