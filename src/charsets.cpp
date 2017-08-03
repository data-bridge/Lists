// Extension of Metaphone3.
// Copyright (C) 2017 by Soren Hein.
// No restrictions on copying and modifying, as long as credit is given.
// No warranties.

#include "charsets.h"


#include <iostream>
void setEntry(
  const unsigned page,
  const unsigned high,
  const char mappedChar,
  CharTables& charTables)
{
  const unsigned pshift = page - 0xC3;
  const unsigned shift = high - 0x80;
  charTables.UTF8[pshift][shift] = mappedChar;
}


void setEntry(
  const unsigned page,
  const unsigned high,
  const char mappedChar,
  const bool isVowel,
  CharTables& charTables)
{
  setEntry(page, high, mappedChar, charTables);

  const unsigned shift = high - 0x80;
// cout << "shift " << shift << endl;
  charTables.extASCII[shift] = mappedChar;
  charTables.isVowel[shift] = isVowel;
}


void setEntry(
  const unsigned page,
  const unsigned high,
  const char ASCII,
  const int extendedHigh,
  CharTables& tablesASCII,
  CharTables& tablesExtend)
{
  const bool isVowel = (ASCII == 'A' || ASCII == 'E' || 
    ASCII == 'I' || ASCII == 'O' || ASCII == 'U' || ASCII == 'Y');

  setEntry(page, high, ASCII, isVowel, tablesASCII);

  const char mappedChar = static_cast<char>(extendedHigh - 0x100);
// cout << "extHigh " << extendedHigh << ": " << mappedChar << endl;
  setEntry(page, high, mappedChar, isVowel, tablesExtend);
// cout << "mapped: " << mappedChar << endl;
// const unsigned char c = 0xE9;
// const unsigned char c = 'é';
// printf("printf %c\n", c);
// cout << "pos 0A: " << tablesASCII.extASCII[0] << endl;
// cout << "pos 0E: " << tablesExtend.extASCII[0] << endl;
}


void setCharTables(
  CharTables& tA,
  CharTables& tE)
{
  // The symbols in the comments below are UTF-8!
  
  for (unsigned i = 0; i < 0x40; i++)
  {
    tA.extASCII[i] = 0;
    tA.isVowel[i] = false;

    tE.extASCII[i] = 0;
    tE.isVowel[i] = false;
  }

  setEntry(0xC3, 0x80, 'A', 0xC0, tA, tE); // À, A grave
  setEntry(0xC3, 0x81, 'A', 0xC1, tA, tE); // Á, A acute
  setEntry(0xC3, 0x82, 'A', 0xC2, tA, tE); // Â, A circumflex
  setEntry(0xC3, 0x83, 'A', 0xC3, tA, tE); // Ã, A tilde
  setEntry(0xC3, 0x84, 'A', 0xC4, tA, tE); // Ä, A diaeresis
  setEntry(0xC3, 0x85, 'A', 0xC5, tA, tE); // Å, A with ring, AA
  setEntry(0xC3, 0x86, 'A', 0xC6, tA, tE); // Æ, AE
  setEntry(0xC3, 0x87, 'S', 0xC7, tA, tE); // Ç, C cedilla
  setEntry(0xC3, 0x88, 'E', 0xC8, tA, tE); // È, E grave
  setEntry(0xC3, 0x89, 'E', 0xC9, tA, tE); // É, E acute
  setEntry(0xC3, 0x8A, 'E', 0xCA, tA, tE); // Ê, E circumflex
  setEntry(0xC3, 0x8B, 'E', 0xCB, tA, tE); // Ë, E diaeresis
  setEntry(0xC3, 0x8C, 'I', 0xCC, tA, tE); // Ì, I grave
  setEntry(0xC3, 0x8D, 'I', 0xCD, tA, tE); // Í, I acute
  setEntry(0xC3, 0x8E, 'I', 0xCE, tA, tE); // Î, I circumflex
  setEntry(0xC3, 0x8F, 'I', 0xCF, tA, tE); // Ï, I diaeresis

  setEntry(0xC3, 0x90, 'D', 0xD0, tA, tE); // Ð, ETH capital
  setEntry(0xC3, 0x91, 'N', 0xD1, tA, tE); // Ñ, N tilde
  setEntry(0xC3, 0x92, 'O', 0xD2, tA, tE); // Ò, O grave
  setEntry(0xC3, 0x93, 'O', 0xD3, tA, tE); // Ó, O acute
  setEntry(0xC3, 0x94, 'O', 0xD4, tA, tE); // Ô, O circumflex
  setEntry(0xC3, 0x95, 'O', 0xD5, tA, tE); // Õ, O tilde
  setEntry(0xC3, 0x96, 'O', 0xD6, tA, tE); // Ö, O diaeresis
  setEntry(0xC3, 0x97,  0 , 0xD7, tA, tE); // -, times
  setEntry(0xC3, 0x98, 'O', 0xD8, tA, tE); // Ø, O slash, OE
  setEntry(0xC3, 0x99, 'U', 0xD9, tA, tE); // Ù, U grave
  setEntry(0xC3, 0x9A, 'U', 0xDA, tA, tE); // Ú, U acute
  setEntry(0xC3, 0x9B, 'U', 0xDB, tA, tE); // Û, U circumflex
  setEntry(0xC3, 0x9C, 'U', 0xDC, tA, tE); // Ü, U diaeresis
  setEntry(0xC3, 0x9D, 'Y', 0xDD, tA, tE); // Ý, Y acute
  setEntry(0xC3, 0x9E, '0', 0xDE, tA, tE); // Þ, THORN capital
  setEntry(0xC3, 0x9F, 'S', 0xDF, tA, tE); // ß, sz

  setEntry(0xC3, 0xA0, 'A', 0xE0, tA, tE); // à, a grave
  setEntry(0xC3, 0xA1, 'A', 0xE1, tA, tE); // á, a acute
  setEntry(0xC3, 0xA2, 'A', 0xE2, tA, tE); // â, a circumflex
  setEntry(0xC3, 0xA3, 'A', 0xE3, tA, tE); // ã, a tilde
  setEntry(0xC3, 0xA4, 'A', 0xE4, tA, tE); // ä, a diaeresis
  setEntry(0xC3, 0xA5, 'A', 0xE5, tA, tE); // å, a with ring, AA
  setEntry(0xC3, 0xA6, 'A', 0xE6, tA, tE); // æ, ae
  setEntry(0xC3, 0xA7, 'S', 0xE7, tA, tE); // ç, c cedilla
  setEntry(0xC3, 0xA8, 'E', 0xE8, tA, tE); // è, e grave
  setEntry(0xC3, 0xA9, 'E', 0xE9, tA, tE); // é, e acute
  setEntry(0xC3, 0xAA, 'E', 0xEA, tA, tE); // ê, e circumflex
  setEntry(0xC3, 0xAB, 'E', 0xEB, tA, tE); // ë, e diaeresis
  setEntry(0xC3, 0xAC, 'I', 0xEC, tA, tE); // ì, i grave
  setEntry(0xC3, 0xAD, 'I', 0xED, tA, tE); // í, i acute
  setEntry(0xC3, 0xAE, 'I', 0xEE, tA, tE); // î, i circumflex
  setEntry(0xC3, 0xAF, 'I', 0xEF, tA, tE); // ï, i diaeresis

  setEntry(0xC3, 0xB0, 'D', 0xF0, tA, tE); // ð, eth lower-case
  setEntry(0xC3, 0xB1, 'N', 0xF1, tA, tE); // ñ, n tilde
  setEntry(0xC3, 0xB2, 'O', 0xF2, tA, tE); // ò, o grave
  setEntry(0xC3, 0xB3, 'O', 0xF3, tA, tE); // ó, o acute
  setEntry(0xC3, 0xB4, 'O', 0xF4, tA, tE); // ô, o circumflex
  setEntry(0xC3, 0xB5, 'O', 0xF5, tA, tE); // õ, o tilde
  setEntry(0xC3, 0xB6, 'O', 0xF6, tA, tE); // ö, o diaeresis
  setEntry(0xC3, 0xB8, 'O', 0xF8, tA, tE); // ø, o slash, oe
  setEntry(0xC3, 0xB9, 'U', 0xF9, tA, tE); // ù, u grave
  setEntry(0xC3, 0xBA, 'U', 0xFA, tA, tE); // ú, u acute
  setEntry(0xC3, 0xBB, 'U', 0xFB, tA, tE); // û, u circumflex
  setEntry(0xC3, 0xBC, 'U', 0xFC, tA, tE); // ü, u diaeresis
  setEntry(0xC3, 0xBD, 'Y', 0xFD, tA, tE); // ý, y acute
  setEntry(0xC3, 0xBE, '0', 0xFE, tA, tE); // þ, thorn lower-case
  setEntry(0xC3, 0xBF, 'S', 0xFF, tA, tE); // ÿ, y diaeresis

  setEntry(0xC4, 0x80, 'A', tA); // Ā, A macron
  setEntry(0xC4, 0x81, 'A', tA); // ā, a macron
  setEntry(0xC4, 0x82, 'A', tA); // Ă, A breve
  setEntry(0xC4, 0x83, 'A', tA); // ă, a breve
  setEntry(0xC4, 0x84, 'A', tA); // Ą, A ogonek
  setEntry(0xC4, 0x85, 'A', tA); // ą, a ogonek
  setEntry(0xC4, 0x86, 'C', tA); // Ć, C acute
  setEntry(0xC4, 0x87, 'C', tA); // ć, c acute
  setEntry(0xC4, 0x88, 'C', tA); // Ĉ, C circumflex
  setEntry(0xC4, 0x89, 'C', tA); // ĉ, c circumflex
  setEntry(0xC4, 0x8A, 'C', tA); // Ċ, C dot
  setEntry(0xC4, 0x8B, 'C', tA); // ċ, c dot
  setEntry(0xC4, 0x8C, 'C', tA); // Č, C caron
  setEntry(0xC4, 0x8D, 'C', tA); // č, c caron
  setEntry(0xC4, 0x8E, 'D', tA); // Ď, D caron
  setEntry(0xC4, 0x8F, 'D', tA); // ď, d caron

  setEntry(0xC4, 0x90, 'D', tA); // Đ, D stroke
  setEntry(0xC4, 0x91, 'D', tA); // đ, d stroke
  setEntry(0xC4, 0x92, 'E', tA); // Ē, E macron
  setEntry(0xC4, 0x93, 'E', tA); // ē, e macron
  setEntry(0xC4, 0x94, 'E', tA); // Ĕ, E breve
  setEntry(0xC4, 0x95, 'E', tA); // ĕ, e breve
  setEntry(0xC4, 0x96, 'E', tA); // Ė, E dot
  setEntry(0xC4, 0x97, 'E', tA); // ė, e dot
  setEntry(0xC4, 0x98, 'E', tA); // Ę, E ogonek
  setEntry(0xC4, 0x99, 'E', tA); // ę, e ogonek
  setEntry(0xC4, 0x9A, 'E', tA); // Ě, E caron
  setEntry(0xC4, 0x9B, 'E', tA); // ě, e caron
  setEntry(0xC4, 0x9C, 'G', tA); // Ĝ, G circumflex
  setEntry(0xC4, 0x9D, 'G', tA); // ĝ, g circumflex
  setEntry(0xC4, 0x9E, 'G', tA); // Ğ, G breve
  setEntry(0xC4, 0x9F, 'G', tA); // ğ, g breve

  setEntry(0xC4, 0xA0, 'G', tA); // Ġ, G dot
  setEntry(0xC4, 0xA1, 'G', tA); // ġ, g dot
  setEntry(0xC4, 0xA2, 'G', tA); // Ģ, G cedilla
  setEntry(0xC4, 0xA3, 'G', tA); // ģ, g cedilla
  setEntry(0xC4, 0xA4, 'H', tA); // Ĥ, H circumflex
  setEntry(0xC4, 0xA5, 'H', tA); // ĥ, h circumflex
  setEntry(0xC4, 0xA6, 'H', tA); // Ħ, H stroke
  setEntry(0xC4, 0xA7, 'H', tA); // ħ, h stroke
  setEntry(0xC4, 0xA8, 'I', tA); // Ĩ, I tilde
  setEntry(0xC4, 0xA9, 'I', tA); // ĩ, i tilde
  setEntry(0xC4, 0xAA, 'I', tA); // Ī, I macron
  setEntry(0xC4, 0xAB, 'I', tA); // ī, i macron
  setEntry(0xC4, 0xAC, 'I', tA); // Ĭ, I breve
  setEntry(0xC4, 0xAD, 'I', tA); // ĭ, i breve
  setEntry(0xC4, 0xAE, 'I', tA); // Į, I ogonek
  setEntry(0xC4, 0xAF, 'I', tA); // į, i ogonek

  setEntry(0xC4, 0xB0, 'I', tA); // İ, I dot
  setEntry(0xC4, 0xB1, 'I', tA); // ı, i dotless
  setEntry(0xC4, 0xB2, 'J', tA); // Ĳ, IJ ligature
  setEntry(0xC4, 0xB3, 'J', tA); // ĳ, ij ligature
  setEntry(0xC4, 0xB4, 'J', tA); // Ĵ, J circumflex
  setEntry(0xC4, 0xB5, 'J', tA); // ĵ, j circumflex
  setEntry(0xC4, 0xB6, 'K', tA); // Ķ, K cedilla
  setEntry(0xC4, 0xB7, 'K', tA); // ķ, k cedilla
  setEntry(0xC4, 0xB8, 'K', tA); // ĸ, kra small
  setEntry(0xC4, 0xB9, 'L', tA); // Ĺ, L acute
  setEntry(0xC4, 0xBA, 'L', tA); // ĺ, l acute
  setEntry(0xC4, 0xBB, 'L', tA); // Ļ, L cedilla
  setEntry(0xC4, 0xBC, 'L', tA); // ļ, l cedilla
  setEntry(0xC4, 0xBD, 'L', tA); // Ľ, L caron
  setEntry(0xC4, 0xBE, 'L', tA); // ľ, l caron
  setEntry(0xC4, 0xBF, 'L', tA); // Ŀ, L middle dot

  setEntry(0xC5, 0x80, 'L', tA); // ŀ, l middle dot
  setEntry(0xC5, 0x81, 'L', tA); // Ł, L stroke
  setEntry(0xC5, 0x82, 'L', tA); // ł, l stroke
  setEntry(0xC5, 0x83, 'N', tA); // Ń, N acute
  setEntry(0xC5, 0x84, 'N', tA); // ń, n acute
  setEntry(0xC5, 0x85, 'N', tA); // Ņ, N cedilla
  setEntry(0xC5, 0x86, 'N', tA); // ņ, n cedilla
  setEntry(0xC5, 0x87, 'N', tA); // Ň, N caron
  setEntry(0xC5, 0x88, 'N', tA); // ň, n caron
  setEntry(0xC5, 0x89, 'N', tA); // ŉ, apostrophe n
  setEntry(0xC5, 0x8A, 'N', tA); // Ŋ, ENG capital
  setEntry(0xC5, 0x8B, 'N', tA); // ŋ, eng capital
  setEntry(0xC5, 0x8C, 'O', tA); // Ō, O macron
  setEntry(0xC5, 0x8D, 'O', tA); // ō, o macron
  setEntry(0xC5, 0x8E, 'O', tA); // Ŏ, O breve
  setEntry(0xC5, 0x8F, 'O', tA); // ŏ, o breve

  setEntry(0xC5, 0x90, 'O', tA); // Ő, O double acute
  setEntry(0xC5, 0x91, 'O', tA); // ő, o double acute
  setEntry(0xC5, 0x92, 'O', tA); // Œ, OE ligature
  setEntry(0xC5, 0x93, 'O', tA); // œ, oe ligature
  setEntry(0xC5, 0x94, 'R', tA); // Ŕ, R acute
  setEntry(0xC5, 0x95, 'R', tA); // ŕ, r acute
  setEntry(0xC5, 0x96, 'R', tA); // Ŗ, R cedilla
  setEntry(0xC5, 0x97, 'R', tA); // ŗ, r cedilla
  setEntry(0xC5, 0x98, 'R', tA); // Ř, R caron
  setEntry(0xC5, 0x99, 'R', tA); // ř, r caron
  setEntry(0xC5, 0x9A, 'S', tA); // Ś, S acute
  setEntry(0xC5, 0x9B, 'S', tA); // ś, s acute
  setEntry(0xC5, 0x9C, 'S', tA); // Ŝ, S circumflex
  setEntry(0xC5, 0x9D, 'S', tA); // ŝ, s circumflex
  setEntry(0xC5, 0x9E, 'S', tA); // Ş, S cedilla
  setEntry(0xC5, 0x9F, 'S', tA); // ş, s cedilla

  setEntry(0xC5, 0xA0, 'S', tA); // Š, S caron
  setEntry(0xC5, 0xA1, 'S', tA); // š, s caron
  setEntry(0xC5, 0xA2, 'T', tA); // Ţ, T cedilla
  setEntry(0xC5, 0xA3, 'T', tA); // ţ, t cedilla
  setEntry(0xC5, 0xA4, 'T', tA); // Ť, T caron
  setEntry(0xC5, 0xA5, 'T', tA); // ť, t caron
  setEntry(0xC5, 0xA6, 'T', tA); // Ŧ, T stroke
  setEntry(0xC5, 0xA7, 'T', tA); // ŧ, t stroke
  setEntry(0xC5, 0xA8, 'U', tA); // Ũ, U tilde
  setEntry(0xC5, 0xA9, 'U', tA); // ũ, u tilde
  setEntry(0xC5, 0xAA, 'U', tA); // Ū, U macron
  setEntry(0xC5, 0xAB, 'U', tA); // ū, u macron
  setEntry(0xC5, 0xAC, 'U', tA); // Ŭ, U breve
  setEntry(0xC5, 0xAD, 'U', tA); // ŭ, u breve
  setEntry(0xC5, 0xAE, 'U', tA); // Ů, U ring
  setEntry(0xC5, 0xAF, 'U', tA); // ů, u ring

  setEntry(0xC5, 0xB0, 'U', tA); // Ű, U double acute
  setEntry(0xC5, 0xB1, 'U', tA); // ű, u double acute
  setEntry(0xC5, 0xB2, 'U', tA); // Ų, U ogonek
  setEntry(0xC5, 0xB3, 'U', tA); // ų, u ogonek
  setEntry(0xC5, 0xB4, 'W', tA); // Ŵ, W circumflex
  setEntry(0xC5, 0xB5, 'W', tA); // ŵ, w circumflex
  setEntry(0xC5, 0xB6, 'Y', tA); // Ŷ, Y circumflex
  setEntry(0xC5, 0xB7, 'Y', tA); // ŷ, y circumflex
  setEntry(0xC5, 0xB8, 'Y', tA); // Ÿ, Y diaeresis
  setEntry(0xC5, 0xB9, 'Z', tA); // Ź, Z acute
  setEntry(0xC5, 0xBA, 'Z', tA); // ź, z acute
  setEntry(0xC5, 0xBB, 'Z', tA); // Ż, Z dot
  setEntry(0xC5, 0xBC, 'Z', tA); // ż, z dot
  setEntry(0xC5, 0xBD, 'Z', tA); // Ž, Z caron
  setEntry(0xC5, 0xBE, 'Z', tA); // ž, z caron
  setEntry(0xC5, 0xBF, 'S', tA); // ſ, s long

}


void convertToUpper(
  const string& textIn,
  string& textOut,
  const CharTables& charTables)
{
  // This function attempts to combine (some) UTF-8 and (one of the)
  // extended ASCII tables.

  // TODO: Possibly mark up consonants with different pronunciations,
  // e.g. C-cedilla -> S, z-dot, n-tilde etc.
  const unsigned l = textIn.length();
  textOut = "";
  for (unsigned i = 0; i < l; i++)
  {
    const int ci = toupper(static_cast<int>(textIn[i]));
    const char c = static_cast<char>(ci);
    if (c >= 0)
    {
      textOut.push_back(c);
      continue;
    }

    if (i+1 != l && (c == 0xC3 || c == 0xC4 || c == 0xC5))
    {
      const char d = textIn[i+1];
      if (d < -0x40)
      {
        const char u = charTables.UTF8
          [static_cast<unsigned>(ci-0xC3)]
          [static_cast<unsigned>(d+0x80)];
        // Effectively 0x80..0xBF, so most often UTF-8.
        if (u != 0)
        {
          textOut.push_back(u);
          i++;
          continue;
        }
      }
    }

    // Skip this part of the ASCII table, unless perhaps later.
    // http://www.ascii-code.com/
    if (ci < -0x40)
    {
      textOut.push_back('*');
      continue;
    }


    const char e = charTables.extASCII[static_cast<unsigned>(ci+0x40)];
    if (e == 0)
    {
      textOut = "[ERROR]";
      return;
    }
    textOut.push_back(e);
  }
}

