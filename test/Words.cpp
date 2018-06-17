/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/


#include <iostream>
#include <fstream>


Words::Words()
{
  Words::reset();
}


Words::~Words()
{
}


void Words::reset()
{
  encodeVowelsVal = true;
  encodeExactVal = true;

  words.clear();
  indexNextRead = 0;

  wordsMap.clear();
  metaMap.clear();
  collisionsOK.clear();

  wordsCount.clear();
  errorsCount1.clear();
  errorsCount2.clear();
  collisionsCountReal.clear();
}


void Words::rewind()
{
  indexNextRead = 0;
}


char const * Words::next() const
{
  if (indexNext > words.size())
    return nullptr;
  else
    return words[indexNext++].wordp;
}


void Words::setEncoding(
  const bool encodeVowels,
  const bool encodeExact)
{
  encodeVowelsVal = encodeVowels;
  encodeExactVal = encodeExact;
}


void Words::pronToMeta(
  const string& realpron,
  string& mpron) const
{
  // TODO
}


void Words::addReal(
  const string& word,
  const string& realpron,
  const string& cat,
  const string& sub,
  const string& lno)
{
  unsigned i;
  auto it = wordsMap.find(word);
  if (it == wordsMap.end())
  {
    i = words.size();
    words.emplace_back(WordEntry());
  }
  else
    i = it->second;

  WordEntry * entryp = &words.back();

  entryp->word = word;
  strcpy(entryp->word, word.c_str());
  entryp->metapron = "";
  entryp->metapronAlt = "";

  entryp->prons.emplace_back(PronEntry());
  PronEntry& pe = entryp->prons.back();

  pe.pron = realpron;
  Words::PronToMeta(realpron, pe.pron);
  pe.category = cat;
  pe.subcat = sub;
  pe.lines = lno;

  wordsCount[cat][sub]++;
}


bool Words::addMeta(
  const string& word,
  const string& met1,
  const string& met2)
{
  auto it = wordsMap.find(word);
  if (it == wordsMap.end())
    return false;

  const unsigned n = it->second;
  WordEntry& entry = words[n];
  entry.metapron = met1;
  entry.metapronAlt = met2;

  metaMap[met1].insert(n);
  metaMapAlt[met1].insert(n);

  if (met2 != "")
    metaMapAlt[met2].insert(n);

  return true;
}


void Words::addCollisionOK(
  const string& mpron,
  const set<unsigned>& cset)
{
  collisionsOK[mpron] = cset;
}


void Words::findErrors()
{
  for (unsigned i = 0; i < words.size(); i++)
  {
    const WordEntry we = words[i];
    const string& correct = we.metaconv;

    for (unsigned j = 0; j < words[i].prons.size(); j++)
    {
      const string& met1 = words[i].prons[j].metapron;
      const string& met2 = words[i].prons[j].metapronAlt;

      if (met1 == correct)
        continue;

      errors1.emplace_back(ErrorEntry);
      ErrorEntry& e1 = errors1.back();
      e1.wordIndex = i;
      e2.listIndex = j;

      errorsCount1[we.category][we.subcat]++;

      if (met2 == correct)
       continue;

      errors2.emplace_back(ErrorEntry);
      ErrorEntry& e2 = errors2.back();
      e2.wordIndex = i;
      e2.listIndex = j;

      errorsCount2[we.category][we.subcat]++;
    }
  }
}


void Words::findCollision(
  StringIndexMap& mmap,
  StringIndexMap& realmap)
{
  for (auto &it: mmap)
  {
    const string& metapron = it->first;
    set<unsigned>& indexSet = it->second;

    if (indexSet.size() <= 1)
      continue; // No collision
    
    auto itc = collisionsOK.find(metapron);
    if (itc != collisionsOK.end())
    {
      for (auto itok&: * itc)
        indexSet.erase(* itok);
    }

    realmap[metapron] = indexSet;
  }
}


void Words::findCollisions()
{
  Words::findCollision(metaMap, collisionsReal1);
  Words::findCollision(metaMapAlt, collisionsReal2);
}


void Words::printStat(
  ofstream& fout,
  const string& heading,
  const CountMap& count)
{
  // TODO
}


void Words::printStatPercent(
  ofstream& fout,
  const string& heading,
  const CountMap& countDenom,
  const CountMap& countNum)
{
  // TODO
}


void Words::printStats(
  const string& fname,
  const PronFormat format) const
{
  // TODO: Make sorted lists of cats and subs, and pass them on.

  ofstream fout;
  fout.open(fname);
  Words::printStat(fout, "Word counts", wordsCount);
  Words::printStat(fout, "Error counts", errorsCount1);
  Words::printStat(fout, "Error counts with alt", errorsCount2);

  Words::printStatPercent(fout, "Error counts", wordsCount, errorsCount1);
  Words::printStatPercent(fout, "Error counts with alt", wordsCount, errorsCount2);
  fout.close();
}


void Words::printMetapronError(
  ofstream& fout,
  const string& heading,
  const list<ErrorEntry>& errors) const
{
  fout << heading << "\n\n";

  for (auto it&: errors)
  {
    const ErrorEntry& ee = * it;
    const WordEntry& we = words[ee.wordIndex];
    const ErrorEntry& le = we.prons[ee.listIndex];

    fout << we.word << ":\n";
    fout << setw(16) << left << we.metapron <<
      setw(16) << left << we.metapronAlt << "\n";
    fout << le.pron << ", " <<
      le.metaconv << ", " <<
      le.category << ", " <<
      le.subcat << ", " <<
      le.lines << "\n\n";
  }

  fout << "\nNumber of errors: " << errors.size() << "\n\n";
}


void Words::printMetapronErrors(const string& fname) const
{
  ofstream fout;
  fout.open(fname);
  Words::printCollision(fout, "Errors primary", errors1);
  Words::printCollision(fout, "Errors with alt", errors2);
  fout.close();
}


void Words::printCollision(
  ofstream& fout,
  const string& heading,
  const StringIndexMap& collmap) const
{
  fout << heading << "\n\n";

  for (auto it&: collmap)
  {
    fout << "Metapron3: " << it->first << "\n";
    const set<unsigned>& cmap = it->second;

    for (auto itc&: cmap)
    {
      const WordEntry& we = words[* itc];
      fout << "  " << we.word << ", " <<
        we.metapron << ", " << we.metapronAlt << "\n";
    }
  }

  fout << "\nNumber of collisions: " << collmap.size() << "\n\n";
}


void Words::printCollisions(const string& fname) const
{
  ofstream fout;
  fout.open(fname);
  Words::printCollision(fout, "Collisions primary", collisionsReal1);
  Words::printCollision(fout, "Collisions with alt", collisionsReal2);
  fout.close();
}

