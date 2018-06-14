/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_CHARSETS_H
#define PRON_CHARSETS_H

#include <string>

using namespace std;


struct CharTables
{
  // 0xC3..0xC5, then 0x80..0xBF.
  char UTF8[3][0x40];

  // 0xC0..0xFF.
  char extASCII[0x40];

  // 0xC0..0xFF.
  bool isVowel[0x40];
};


void setCharTables(
  CharTables& tablesASCII,
  CharTables& tablesExtend);

void convertToUpper(
  const string& textIn,
  string& textOut,
  const CharTables& charTables);

#endif
