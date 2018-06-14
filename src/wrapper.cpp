/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/


int STDCALL metaword(
  char * word,
  bool encodeVowels,
  bool encodeExact,
  char * best,
  char * alt)
{
}


int STDCALL metalist(
  char ** word,
  int number,
  bool encodeVowels,
  bool encodeExact,
  char ** bests,
  char ** alts)
{
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
