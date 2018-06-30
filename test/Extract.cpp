/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/


#include <iostream>
#include <iomanip>
#include <fstream>

#include "Extract.h"
#include "parse.h"

#define EXTRACT_FILE_REAL "data/pieces_real.dat"
#define EXTRACT_FILE_META "data/pieces_meta.dat"

#define SKIP_FILE "skips.dat"


const vector<string> Consonants =
{
  "b", "c", "d", "f", "g", "h", "j", "k", "l", "m", 
  "n", "p", "q", "r", "s", "t", "v", "x", "z", "'"
};

const vector<string> Vowels =
{
  "a", "e", "i", "o", "u", "w", "y"
};


Extract::Extract()
{
  Extract::reset();
}


Extract::~Extract()
{
}


void Extract::reset()
{
  prontype = EXTRACT_REAL;
}


void Extract::setType(const PronType t)
{
  prontype = t;

  ifstream fin;
  if (prontype == EXTRACT_REAL)
    fin.open(EXTRACT_FILE_REAL);
  else
    fin.open(EXTRACT_FILE_META);

  string line;
  vector<string> tokens;

  while (getline(fin, line))
  {
    if (line == "" || line.front() == '#')
      continue;

    const unsigned c = countDelimiters(line, " ");
    tokens.resize(c+1);
    tokens.clear();
    tokenize(line, tokens, " ");

    const string& part = tokens[0];
    for (unsigned i = 1; i < tokens.size(); i++)
    {
      if (tokens[i] == ".")
        pronMap[part].push_back("");
      else
        pronMap[part].push_back(tokens[i]);
    }

  }

  fin.close();

  fin.open(SKIP_FILE);

  while (getline(fin, line))
  {
    if (line == "" || line.front() == '#')
      continue;

    const unsigned c = countDelimiters(line, " ");
    tokens.resize(c+1);
    tokens.clear();
    tokenize(line, tokens, " ");

    string& part = tokens[0];
    toLower(part);
    skipsMap[part] = true;
  }

  fin.close();

  for (auto &entry: Consonants)
    isVowelMap[entry] = 0;

  for (auto &entry: Vowels)
    isVowelMap[entry] = 1;
}


string Extract::recurseMatch(
  const string& part,
  const string& pron,
  unsigned& lpron)
{
  auto it = pronMap.find(part);
  if (it == pronMap.end())
    return "part " + part + ", pron " + pron + ": no part\n";

  for (auto &candPron: it->second)
  {
    lpron = candPron.size();
    if (lpron == 0)
    {
      histoMap[part]["."]++;
      return "";
    }
    else if (lpron <= pron.size() && candPron == pron.substr(0, lpron))
    {
      // Found a match.
      histoMap[part][candPron]++;
      return "";
    }
  }

  return "part " + part + ", pron " + pron + ": no match\n";
}


string Extract::recurse(
  const string& word,
  const string& pron,
  const bool state)
{
// cout << "enter " << word << ", " << pron << endl;
  for (unsigned i = 0; i < word.size(); i++)
  {
// cout << "i " << i << endl;
    if (isVowelMap[word.substr(i, 1)] == state)
      continue;

    // Change from vowel streak to consonant streak or vice versa.
    const string part = word.substr(0, i);

    auto it = pronMap.find(part);
    if (it == pronMap.end())
      return "part " + part + ", pron " + pron + ": no part\n";
    
    string ret;
    for (auto &candPron: it->second)
    {
      const unsigned lpron = candPron.size();
      string candToLog = "";
      if (lpron == 0)
        candToLog = ".";
      else if (lpron <= pron.size() && candPron == pron.substr(0, lpron))
        candToLog = candPron;
      else
        continue;
// cout << "candidate " << candToLog << endl;

      if (lpron >= pron.size())
      {
// cout << "Used up pron\n";
        ret = recurse(word.substr(i), "", ! state);
        if (ret == "")
        {
          histoMap[part][candToLog]++;
          return "";
        }
      }
      else if (lpron == 0)
      {
// cout << "Empty pron\n";
        ret = recurse(word.substr(i), pron, ! state);
        if (ret == "")
        {
          histoMap[part][candToLog]++;
          return "";
        }
      }
      else
      {
// cout << "General pron\n";
        if (prontype == EXTRACT_REAL)
          ret = recurse(word.substr(i), pron.substr(lpron+1), ! state);
        else
          ret = recurse(word.substr(i), pron.substr(lpron), ! state);

        if (ret == "")
        {
          histoMap[part][candToLog]++;
          return "";
        }
      }
    }

    return ret;
  }

  // Last part of the word.
  unsigned lpron;
  return recurseMatch(word, pron, lpron);
}


void Extract::enter(
  const string& word,
  const string& pron)
{
  string wlower = word;
  toLower(wlower);

  if (wlower.size() == 0)
    return;
  else if (skipsMap.find(wlower) == skipsMap.end())
  {
    const string& r = Extract::recurse(wlower, pron, isVowelMap[wlower.substr(0, 1)]);
    if (r != "")
      // cout << r;
      cout << "FAIL " << word << ", " << pron << ":\n" << r << "\n";
  }

  collisionMap[pron].insert(wlower);
}


void Extract::print(const string& fname) const
{
  ofstream fout;
  fout.open(fname);
  fout.close();
}



void Extract::printCollisions(const string& fname) const
{
  ofstream fout;
  fout.open(fname);

  for (auto &it: collisionMap)
  {
    auto &words = it.second;
    if (words.size() == 1)
      continue;

    fout << "# pron " << it.first << "\n";
    for (auto &word: words)
      fout << word << " ";
    fout << "\n\n";
  }

  fout.close();
}

