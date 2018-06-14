/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#include "../include/pron.h"
#include "../include/portab.h"

#include "Metaphone3.h"


int STDCALL metaword(
  char * word,
  bool encodeVowels,
  bool encodeExact,
  char * best,
  char * alt)
{
  UNUSED(word);
  UNUSED(encodeVowels);
  UNUSED(encodeExact);
  UNUSED(best);
  UNUSED(alt);
  return RETURN_NO_FAULT;
}


int STDCALL metaphrase(
  char * word,
  bool encodeVowels,
  bool encodeExact,
  char * best,
  char * alt)
{
  UNUSED(word);
  UNUSED(encodeVowels);
  UNUSED(encodeExact);
  UNUSED(best);
  UNUSED(alt);
  return RETURN_NO_FAULT;
}


int STDCALL metalist(
  char ** words,
  int number,
  bool encodeVowels,
  bool encodeExact,
  char ** bests,
  char ** alts)
{
  UNUSED(words);
  UNUSED(number);
  UNUSED(encodeVowels);
  UNUSED(encodeExact);
  UNUSED(bests);
  UNUSED(alts);
  return RETURN_NO_FAULT;
}


void STDCALL ErrorMessage(int code, char line[80])
{
  switch (code)
  {
    case RETURN_NO_FAULT:
      strcpy(line, TEXT_NO_FAULT);
      break;
    case RETURN_UNKNOWN_FAULT:
      strcpy(line, TEXT_UNKNOWN_FAULT);
      break;
    default:
      strcpy(line, "Not a Metapron3 error code");
  }
}
