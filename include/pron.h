/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_DLL_H
#define PRON_DLL_H

#if defined(_WIN32) || defined(__CYGWIN__)
  #define DLLEXPORT __declspec(dllexport)
  #define STDCALL __stdcall
#else
  #define DLLEXPORT
  #define STDCALL
  #define INT8 char
#endif

#ifdef __cplusplus
  #define EXTERN_C extern "C"
#else
  #define EXTERN_C
#endif

// Version 1.0.0. Allowing for 2 digit minor versions
#define PRON_VERSION 10100

// Default size of key storage allocation
#define MAX_KEY_ALLOCATION 32

// Default maximum length of encoded key
#define DEFAULT_MAX_KEY_LENGTH 32



// Error codes. See interface document for more detail.
// Call ErrorMessage(code, line[]) to get the text form in line[].

// Success.
#define RETURN_NO_FAULT 1
#define TEXT_NO_FAULT "Success"

#define RETURN_UNKNOWN_FAULT -1
#define TEXT_UNKNOWN_FAULT "General error"


EXTERN_C DLLEXPORT int STDCALL metaword(
  char const * word,
  const bool encodeVowels,
  const bool encodeExact,
  char * best,
  char * alt
  );

EXTERN_C DLLEXPORT int STDCALL metaphrase(
  char const * word,
  const bool encodeVowels,
  const bool encodeExact,
  char * best,
  char * alt
  );

EXTERN_C DLLEXPORT int STDCALL metalist(
  char const ** words,
  const unsigned number,
  const bool encodeVowels,
  const bool encodeExact,
  char ** bests,
  char ** alts
  );

EXTERN_C DLLEXPORT void STDCALL ErrorMessage(
  int code,
  char line[80]);

#endif
