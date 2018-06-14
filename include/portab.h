/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_PORTAB_H
#define PRON_PORTAB_H


#if defined(_WIN32)
  #if defined(__MINGW32__) && !defined(WINVER)
    #define WINVER 0x500
  #endif

  #include <windows.h>
  #include <process.h>

  #define USES_DLLMAIN
  /* DLL uses DllMain() for initialization */

  #if defined (_MSC_VER)
    #include <intrin.h>
  #endif

#elif defined (__CYGWIN__)
  #include <windows.h>
  #include <process.h>

  #define USES_DLLMAIN

#elif defined (__linux)
  #include <unistd.h>
  #define USES_CONSTRUCTOR
  /* DLL uses a constructor function for initialization */

  typedef long long __int64;

#elif defined (__APPLE__)
  #include <unistd.h>

  #define USES_CONSTRUCTOR

  typedef long long __int64;

#endif

//
// http://stackoverflow.com/a/4030983/211160
// Use to indicate a variable is being intentionally not referred to (which
// usually generates a compiler warning)
#ifndef UNUSED
  #define UNUSED(x) ((void)(true ? 0 : ((x), void(), 0)))
#endif

#endif
