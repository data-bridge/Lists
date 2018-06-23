/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_EXTRACT_H
#define PRON_EXTRACT_H

#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;


class Extract
{
  private:

    map<string, vector<string>> pronMap;

    map<string, bool> isVowelMap;

    map<string, map<string, unsigned>> histoMap;


    void setTable();

    string recurseMatch(
      const string& part,
      const string& pron,
      unsigned& lpron);

    string recurse(
      const string& word,
      const string& pron,
      const bool state);


  public:

    Extract();
    ~Extract();
    void reset();

    void enter(
      const string& word,
      const string& pron);

    void enter(const string& fname);

    void print(const string& fname) const;
};

#endif

