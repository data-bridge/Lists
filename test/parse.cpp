/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

// The functions in this file help to parse files.


#include <numeric>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "const.h"

using namespace std;


// tokenize splits a string into tokens separated by delimiter.
// http://stackoverflow.com/questions/236129/split-a-string-in-c

void tokenize(
  const string& text, 
  vector<string>& tokens,
  const string& delimiters)
{
  string::size_type pos, lastPos = 0;

  while (true)
  {
    pos = text.find_first_of(delimiters, lastPos);
    if (pos == std::string::npos)
    {
      pos = text.length();
      tokens.push_back(string(text.data()+lastPos, 
        static_cast<string::size_type>(pos - lastPos)));
      break;
    }
    else
    {
      tokens.push_back(string(text.data()+lastPos,
        static_cast<string::size_type>(pos - lastPos)));
    }
    lastPos = pos + 1;
  }
}


unsigned countDelimiters(
  const string& text,
  const string& delimiters)
{
  int c = 0;
  for (unsigned i = 0; i < delimiters.length(); i++)
    c += static_cast<int>
      (count(text.begin(), text.end(), delimiters.at(i)));
  return static_cast<unsigned>(c);
}


// https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.2B.2B
unsigned levenshtein(
  const string& s1,
  const string& s2)
{
  unsigned s1len = s1.size();
  unsigned s2len = s2.size();

  auto column_start = (decltype(s1len))1;

  auto column = new decltype(s1len)[s1len + 1];
  std::iota(column + column_start, column + s1len + 1, column_start);

  for (auto x = column_start; x <= s2len; x++)
  {
    column[0] = x;
    auto last_diagonal = x - column_start;
    for (auto y = column_start; y <= s1len; y++)
    {
      auto old_diagonal = column[y];
      auto possibilities =
      {
        column[y] + 1,
        column[y - 1] + 1,
        last_diagonal + (s1[y - 1] == s2[x - 1]? 0 : 1)
      };
      column[y] = min(possibilities);
      last_diagonal = old_diagonal;
    }
  }
  auto result = column[s1len];
  delete[] column;
  return result;
}


void toUpper(
  string& text)
{
  for (unsigned i = 0; i < text.size(); i++)
    text.at(i) = static_cast<char>(toupper(static_cast<int>(text.at(i))));
}


void toLower(
  string& text)
{
  for (unsigned i = 0; i < text.size(); i++)
    text.at(i) = static_cast<char>(tolower(static_cast<int>(text.at(i))));
}


Format ext2format(const string& text)
{
  string st = text;
  toUpper(st);

  if (st == "TXT")
    return PRON_FORMAT_TXT;
  else if (st == "CSV")
    return PRON_FORMAT_CSV;
  else
    return PRON_FORMAT_SIZE;
}

