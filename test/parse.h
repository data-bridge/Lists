/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_PARSE_H
#define PRON_PARSE_H

#include <string>
#include <vector>

#include "const.h"

using namespace std;


void tokenize(
  const string& text,
  vector<string>& tokens,
  const string& delimiters);

unsigned countDelimiters(
  const string& text,
  const string& delimiters);

void splitIntoWords(
  const string& text,
  vector<string>& words);

unsigned levenshtein(
  const string& s1,
  const string& s2);

void toUpper(
  string& text);

void toLower(
  string& text);

Format ext2format(
  const string& text);

#endif
