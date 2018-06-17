/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_FILES_H
#define PRON_FILES_H

#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "../include/pron.h"

using namespace std;


struct PronEntry
{
  string pron;
  string metaconv; // pron converted to Metapron3
  string category;
  string subcat;
  string lines;
};


struct WordEntry
{
  string word;
  char wordp[MAX_KEY_ALLOCATION];
  string metapron;
  string metapronAlt;

  list<PronEntry> prons;
};

typedef map<string, map<string, unsigned>> CountMap;
typedef map<string, set<unsigned>> StringIndexMap;

struct ErrorEntry
{
  unsigned wordIndex;
  unsigned listIndex;
};


class Words
{
  private:

    bool encodeVowelsVal;
    bool encodeExactVal;

    vector<WordEntry> words;
    unsigned indexNextRead;

    // wordsMap{aardvark} is the words index of that word.
    map<string, unsigned> wordsMap;

    // metaMap{ARTVARK} is a set of all indices of words
    // that have this Metapron3 pronounciation.
    StringIndexMap metaMap; 

    // metamapAlt is for metapron and metapronAlt combined.
    StringIndexMap metaMapAlt; 

    // Pairs of acceptable collisions.
    StringIndexMap collisionsOK; 

    // Real collisions.
    StringIndexMap collisionsReal1; 
    StringIndexMap collisionsReal2; 

    // List of pronunciation errors.
    list<ErrorEntry> errors1;
    list<ErrorEntry> errors2;

    CountMap wordsCount;

    // The translated pron (metaconv) does not match metapron.
    CountMap errorsCount1;
    
    // Ditto for metapron and metapronAlt combined.
    CountMap errorsCount2;


    void pronToMeta(
      const string& realpron,
      string& mpron) const;

    void findCollision(
      StringIndexMap& mmap,
      StringIndexMap& realmap);

    void printStat(
      ofstream& fout,
      const string& heading,
      const CountMap& count) const;
      
    void printStatPercent(
      ofstream& fout,
      const string& heading,
      const CountMap& countDenom,
      const CountMap& countNum) const;
      
    void printMetapronError(
      ofstream& fout,
      const string& heading,
      const list<ErrorEntry>& errors) const;

    void printCollision(
      ofstream& fout,
      const string& heading,
      StringIndexMap& collmap);

  public:

    Words();
    ~Words();
    void reset();

    void rewind();
    char const * next() const;

    void setEncoding(
      const bool encodeVowels,
      const bool encodeExact);

    void addReal(
      const string& word,
      const string& realpron,
      const string& cat,
      const string& sub,
      const string& lno);

    bool addMeta(
      const string& word,
      const string& met1,
      const string& met2);

    void addCollisionOK(
      const string& mpron,
      const set<unsigned>& cset);

    void findErrors();

    void findCollisions();

    void printStats(
      const string& fname,
      const PronFormat format) const;

    void printMetapronErrors(
      const string& fname) const;

    void printCollisions(
      const string& fname) const;
};

#endif
