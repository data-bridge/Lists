// Extension of Metaphone3.
// Copyright (C) 2017 by Soren Hein.
// No restrictions on copying and modifying, as long as credit is given.
// No warranties.

#ifndef CHARSETS_H
#define CHARSETS_H

#include <string>
// #include <vector>

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

#endif CHARSETS_H
