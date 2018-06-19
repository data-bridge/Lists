/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#include <vector>

#include "../include/pron.h"
#include "../include/portab.h"

#include "Metaphone3.h"


Metaphone3 mph;


void tokenize(
  const string& text,
  vector<string>& tokens,
  const string& delimiters);


int STDCALL metaword(
  char const * word,
  const bool encodeVowels,
  const bool encodeExact,
  char * best,
  char * alt)
{
  mph.setEncodeVowels(encodeVowels);
  mph.setEncodeExact(encodeExact);

  string t(word);
  mph.setWord(t);
  mph.encode();

  strcpy(best, mph.getMetaph().c_str());
  strcpy(alt, mph.getAlternateMetaph().c_str());

  return RETURN_NO_FAULT;
}


int STDCALL metaphrase(
  char const * word,
  const bool encodeVowels,
  const bool encodeExact,
  char * best,
  char * alt)
{
  vector<string> tokens;
  tokens.clear();

  string words(word);
  tokenize(words, tokens, " ");

  mph.setEncodeVowels(encodeVowels);
  mph.setEncodeExact(encodeExact);

  string res = "";
  string resAlt = "";

  for (unsigned i = 0; i < tokens.size(); i++)
  {
    mph.setWord(tokens[i]);
    mph.encode();

    res += mph.getMetaph() + " ";
    resAlt += mph.getAlternateMetaph() + " ";
  }

  if (res != "")
    res.pop_back();
  if (resAlt != "")
    resAlt.pop_back();

  strcpy(best, res.c_str());
  strcpy(alt, res.c_str());

  return RETURN_NO_FAULT;
}


int STDCALL metalist(
  char const ** words,
  const unsigned number,
  const bool encodeVowels,
  const bool encodeExact,
  char ** bests,
  char ** alts)
{
  mph.setEncodeVowels(encodeVowels);
  mph.setEncodeExact(encodeExact);

  string res = "";
  string resAlt = "";

  for (unsigned i = 0; i < number; i++)
  {
    string t(words[i]);
    mph.setWord(t);
    mph.encode();

    strcpy(bests[i], mph.getMetaph().c_str());
    strcpy(alts[i], mph.getAlternateMetaph().c_str());
  }

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

