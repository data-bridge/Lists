/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/


#include <iostream>
#include <iomanip>
#include <fstream>

#include "Words.h"
#include "parse.h"

#define WIDTH 8


const vector<vector<string>> PronList =
{
  {"&", "", "A", "", "A"},
  {"@", "", "A", "", "A"},
  {"(@)", "", "A", "", "A"},
  {"-", "", "A", "", "A"},
  {"A", "", "A", "", "A"},
  {"AU", "", "A", "", "A"},
  {"aI", "", "A", "", "A"},
  {"E", "", "A", "", "A"},
  {"eI", "", "A", "", "A"},
  {"I", "", "A", "", "A"},
  {"i", "", "A", "", "A"},
  {"j", "", "A", "", "A"},
  {"O", "", "A", "", "A"},
  {"Oi", "", "A", "", "A"},
  {"oU", "", "A", "", "A"},
  {"U", "", "A", "", "A"},
  {"u", "", "A", "", "A"},
  {"w", "", "A", "", "A"},
  {"y", "", "A", "", "A"},
  {"Y", "", "A", "", "A"},

  {"b", "P", "P", "B", "B"},
  {"c", "S", "S", "S", "S"},
  {"D", "0", "0", "0", "0"}, // Zero
  {"d", "T", "T", "D", "D"},
  {"dZ", "J", "J", "J", "J"},
  {"f", "F", "F", "F", "F"},
  {"g", "K", "K", "G", "G"},
  {"h", "H", "H", "H", "H"},
  {"k", "K", "K", "K", "K"},
  {"l", "L", "L", "L", "L"},
  {"m", "M", "M", "M", "M"},
  {"N", "NK", "NK", "NG", "NG"},
  {"n", "N", "N", "N", "N"},
  {"p", "P", "P", "P", "P"},
  {"r", "R", "R", "R", "R"},
  {"R", "R", "R", "R", "R"},
  {"S", "X", "X", "X", "X"},
  {"s", "S", "S", "S", "S"},
  {"T", "0", "0", "0", "0"}, // Zero
  {"t", "T", "T", "T", "T"},
  {"tS", "X", "X", "X", "X"},
  {"v", "F", "F", "V", "V"},
  {"x", "X", "X", "X", "X"},
  {"Z", "J", "J", "J", "J"},
  {"z", "S", "S", "S", "S"}

};


Words::Words()
{
  Words::reset();
  Words::setTable();
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
  indexNextPronRead = 0;

  wordsMap.clear();
  metaMap.clear();
  collisionsOK.clear();

  wordsCount.clear();
  errorsCount1.clear();
  errorsCount2.clear();
}


void Words::setTable()
{
  // The index is 2*encodeExact + encodeVowels, so
  //     vowels  exact
  // 0:   false  false
  // 1:    true  false
  // 2:   false   true
  // 3:    true   true

  metapronMap.resize(4);

  for (auto &e: PronList)
  {
    const string& k = e[0];
    metapronMap[0][k] = e[1];
    metapronMap[1][k] = e[2];
    metapronMap[2][k] = e[3];
    metapronMap[3][k] = e[4];
  }
}


void Words::rewind()
{
  indexNextRead = 0;
  indexNextPronRead = 0;
}


char const * Words::next()
{
  if (indexNextRead >= words.size())
    return nullptr;
  else
    return words[indexNextRead++].wordp;
}


bool Words::nextMeta(
  string& word,
  string& mpron)
{
  if (indexNextRead >= words.size())
    return nullptr;
  else
  {
    word = words[indexNextRead].word;
    mpron = words[indexNextRead].metapron;
    indexNextRead++;
    return true;
  }
}


bool Words::nextPair(
  string& word,
  string& pron)
{
  const unsigned lw = words.size();
  if (indexNextRead >= lw)
    return false;

  const unsigned lp = words[indexNextRead].prons.size();
  if (indexNextRead+1 == lw && indexNextPronRead >= lp)
    return false;

  word = words[indexNextRead].word;
  pron = words[indexNextRead].prons[indexNextPronRead].pron;

  indexNextPronRead++;
  if (indexNextPronRead == lp)
  {
    indexNextRead++;
    indexNextPronRead = 0;
  }

  return true;
}


void Words::setEncoding(
  const bool encodeVowels,
  const bool encodeExact)
{
  encodeVowelsVal = encodeVowels;
  encodeExactVal = encodeExact;
}


void Words::pronToMeta(
  const string& word,
  const string& realpron,
  string& mpron) const
{
  const unsigned i = 2*encodeExactVal + encodeVowelsVal;

  const unsigned c = countDelimiters(realpron, "/");
  vector<string> tokens(c+1);
  tokens.clear();
  tokenize(realpron, tokens, "/");

  mpron = "";
  string prevChar = "";

  if (! encodeVowelsVal)
  {
    // A leading vowel still gets encoded.
    auto it = metapronMap[i].find(tokens[0]);
    if (it == metapronMap[i].end())
    {
      cout << "realpron '" << realpron << "': Cannot match " << 
        tokens[0] << "\n";
    }

    if (it->second == "") // Vowel
    {
      mpron = "A";
      prevChar = "A";
    }
  }

  for (auto &t: tokens)
  {
    auto it = metapronMap[i].find(t);
    if (it == metapronMap[i].end())
    {
      cout << "realpron '" << realpron << "': Cannot match " << t << "\n";
      continue;
    }

    // Don't repeat.
    const string& nextChunk = it->second;
    if (nextChunk != prevChar)
    {
      // adherend, anharmonic, backhanded, bathhouse.
      if (nextChunk == "H" && 
         (prevChar == "T" || prevChar == "N" ||
          prevChar == "K" || prevChar == "0" ||
          prevChar == "L" || prevChar == "S" ||
          prevChar == "P" || prevChar == "R"))
        continue;

      mpron += nextChunk;
      prevChar = nextChunk.back();
    }
  }

  // seance: SNS -> SNTS in Metapron3.
  const unsigned l = mpron.size();
  if (l >= 3 && mpron.substr(l-2) == "NS")
  {
    const unsigned lw = word.size();
    const string& end = word.substr(lw-3);
    if (lw >= 4 && 
       (end == "nce" || end == "ncy"))
    {
      // This assumes encodeVowels == false.
    // TODO Look up better C++ solution.
 // cout << "before '" << mpron << "'\n";
    mpron.erase(l-1);
    mpron += "TS";
 // cout << "after  '" << mpron << "'\n";
    }
  }
}


void Words::fnameToTags(
  const string& fname,
  string& cat,
  string& sub) const
{
  const unsigned c = countDelimiters(fname, "/");
  if (c == 0)
  {
    cat = "none";
    sub = "none";
    return;
  }

  vector<string> tokens(c+1);
  tokens.clear();
  tokenize(fname, tokens, "/");

  const unsigned p = tokens[c].find_first_of(".");
  if (p == string::npos)
  {
    cat = tokens[c-1];
    sub = fname;
  }
  else
  {
    cat = tokens[c-1];
    sub = tokens[c].substr(0, p);
  }
}


bool Words::lineToComps(
  const string& line,
  string& w, // Word
  string& lno, // Line numbers
  string& pr, // Pronunciation
  string& vw, // Vowels in word
  string& vp) const // Vowels in pronunciation
{
  const unsigned c = countDelimiters(line, " ");
  if (c != 4)
    return false;

  vector<string> tokens(c+1);
  tokens.clear();
  tokenize(line, tokens, " ");

  w = tokens[0];
  lno = tokens[1];
  pr = tokens[2];
  vw = tokens[3];
  vp = tokens[4];
  return true;
}


void Words::ingestFile(const string& fname)
{
  string cat, sub;
  Words::fnameToTags(fname, cat, sub);

  categories.insert(cat);
  subcats.insert(sub);

  ifstream fin;
  fin.open(fname);
  string line;
  string w, lno, pr, vw, vp;

  while (getline(fin, line))
  {
    if (line == "" || line.front() == '#')
      continue;

    if (! Words::lineToComps(line, w, lno, pr, vw, vp))
    {
      cout << "fname " << fname << ": Could not parse '" << line << "'\n";
      continue;
    }

    Words::addReal(w, pr, cat, sub, lno);
  }

  fin.close();
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
    wordsMap[word] = i;
  }
  else
    i = it->second;

  WordEntry * entryp = &words[i];

  entryp->word = word;
  strcpy(entryp->wordp, word.c_str());
  entryp->metapron = "";
  entryp->metapronAlt = "";

  entryp->prons.emplace_back(PronEntry());
  PronEntry& pe = entryp->prons.back();

  pe.pron = realpron;
  Words::pronToMeta(word, realpron, pe.metaconv);
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
    const string& candidate1 = we.metapron;
    const string& candidate2 = we.metapronAlt;

    for (unsigned j = 0; j < words[i].prons.size(); j++)
    {
      const PronEntry& pe = words[i].prons[j];
      const string& correct = pe.metaconv;

      if (correct == candidate1)
        continue;

      errors1.emplace_back(ErrorEntry());
      ErrorEntry& e1 = errors1.back();
      e1.wordIndex = i;
      e1.listIndex = j;

      errorsCount1[pe.category][pe.subcat]++;

      if (correct == candidate2)
       continue;

      errors2.emplace_back(ErrorEntry());
      ErrorEntry& e2 = errors2.back();
      e2.wordIndex = i;
      e2.listIndex = j;

      errorsCount2[pe.category][pe.subcat]++;
    }
  }
}


void Words::findCollision(
  StringIndexMap& mmap,
  StringIndexMap& realmap)
{
  for (auto &it: mmap)
  {
    const string& metapron = it.first;
    set<unsigned>& indexSet = it.second;

    if (indexSet.size() <= 1)
      continue; // No collision
    
    auto itc = collisionsOK.find(metapron);
    if (itc != collisionsOK.end())
    {
      for (auto &itok: itc->second)
        indexSet.erase(itok);
    }

    realmap[metapron] = indexSet;
  }
}


void Words::findCollisions()
{
  Words::findCollision(metaMap, collisionsReal1);
  Words::findCollision(metaMapAlt, collisionsReal2);
}


string Words::shorten(const string& s) const
{
  if (s.size() <= WIDTH)
    return s;
  else
    return s.substr(0, WIDTH-1) + ".";
}


unsigned Words::lookup(
  const CountMap& count,
  const string& cat,
  const string& sub) const
{
  auto itc = count.find(cat);
  if (itc == count.end())
    return 0;

  const map<string, unsigned>& smap = itc->second;
  auto its = smap.find(sub);
  if (its == smap.end())
    return 0;
  else
    return its->second;
}


unsigned Words::lookup(
  const map<string, unsigned>& count,
  const string& cat) const
{
  auto itc = count.find(cat);
  if (itc == count.end())
    return 0;
  else
    return itc->second;
}


void Words::printStatTXT(
  ofstream& fout,
  const string& heading,
  const CountMap& count) const
{
  fout << heading << "\n\n";

  fout << setw(8) << "";
  for (auto &c: categories)
    fout << setw(8) << right << Words::shorten(c);
  fout << setw(8) << right << "Sum" << "\n";

  map<string, unsigned> catsum;
  for (auto &s: subcats)
  {
    unsigned sum = 0;
    fout << setw(8) << left << Words::shorten(s);
    for (auto &c: categories)
    {
      const unsigned cval = Words::lookup(count, c, s);
      if (cval == 0)
        fout << setw(8) << right << "-";
      else
        fout << setw(8) << right << cval;

      sum += cval;
      catsum[c] += cval;
    }
    fout << setw(8) << right << sum << "\n";
  }

  fout << setw(8) << left << "Sum";
  for (auto &c: categories)
  {
    const unsigned cval = Words::lookup(catsum, c);
    if (cval == 0)
      fout << setw(8) << right << "-";
    else
      fout << setw(8) << right << cval;
  }

  fout << "\n\n";
}


void Words::printStatCSV(
  ofstream& fout,
  const string& heading,
  const CountMap& count) const
{
  fout << heading << "\n\n";

  for (auto &c: categories)
    fout << "," << Words::shorten(c);
  fout << ",Sum\n";

  map<string, unsigned> catsum;
  for (auto &s: subcats)
  {
    unsigned sum = 0;
    fout << Words::shorten(s);
    for (auto &c: categories)
    {
      const unsigned cval = Words::lookup(count, c, s);
      fout << "," << cval;
      sum += cval;
      catsum[c] += cval;
    }
    fout << "," << sum << "\n";
  }

  fout << "Sum";
  for (auto &c: categories)
    fout << "," << Words::lookup(catsum, c);

  fout << "\n\n";
}


void Words::printStat(
  ofstream& fout,
  const string& heading,
  const CountMap& count,
  const Format format) const
{
  if (format == PRON_FORMAT_TXT)
    Words::printStatTXT(fout, heading, count);
  else if (format == PRON_FORMAT_CSV)
    Words::printStatCSV(fout, heading, count);
}


void Words::printStatPercentTXT(
  ofstream& fout,
  const string& heading,
  const CountMap& countDenom,
  const CountMap& countNum) const
{
  fout << heading << "\n\n";

  fout << setw(8) << "";
  for (auto &c: categories)
    fout << setw(8) << right << Words::shorten(c);
  fout << setw(8) << right << "Overall" << "\n";

  map<string, unsigned> catsumDenom;
  map<string, unsigned> catsumNum;

  for (auto &s: subcats)
  {
    unsigned sumDenom = 0;
    unsigned sumNum = 0;

    fout << setw(8) << left << Words::shorten(s);
    for (auto &c: categories)
    {
      const unsigned cDenom = Words::lookup(countDenom, c, s);
      const unsigned cNum = Words::lookup(countNum, c, s);
      if (cDenom == 0 || cNum == 0)
      {
        fout << setw(8) << right << "-";
        continue;
      }

      fout << setw(7) << right << fixed << setprecision(2) << 
        100. * cNum / static_cast<float>(cDenom) << "%";
      sumDenom += cDenom;
      sumNum += cNum;

      catsumDenom[c] += cDenom;
      catsumNum[c] += cNum;
    }

    if (sumDenom == 0)
      fout << setw(8) << "-" << "\n";
    else
      fout << setw(7) << right << right << fixed << setprecision(2) <<
        100. * sumNum / static_cast<float>(sumDenom) << "%\n";
  }

  fout << setw(8) << left << "Overall";
  for (auto &c: categories)
  {
    const unsigned cDenom = Words::lookup(catsumDenom, c);
    const unsigned cNum = Words::lookup(catsumNum, c);

    if (cDenom == 0 || cNum == 0)
      fout << setw(8) << right << "-";
    else
      fout << setw(7) << right << fixed << setprecision(2) <<
        100. * cNum / static_cast<float>(cDenom) << "%";
  }

  fout << "\n";
}


void Words::printStatPercentCSV(
  ofstream& fout,
  const string& heading,
  const CountMap& countDenom,
  const CountMap& countNum) const
{
  fout << heading << "\n\n";

  for (auto &c: categories)
    fout << "," << c;
  fout << ",Overall\n";

  map<string, unsigned> catsumDenom;
  map<string, unsigned> catsumNum;

  for (auto &s: subcats)
  {
    unsigned sumDenom = 0;
    unsigned sumNum = 0;

    fout << s;
    for (auto &c: categories)
    {
      auto itcDenom = countDenom.find(c);
      if (itcDenom == countDenom.end())
      {
        fout << ",0";
        continue;
      }

      const map<string, unsigned>& smapDenom = itcDenom->second;
      auto itsDenom = smapDenom.find(s);
      if (itsDenom == smapDenom.end() || itsDenom->second == 0)
      {
        fout << ",0";
        continue;
      }

      auto itcNum = countNum.find(c);
      if (itcNum == countNum.end())
      {
        fout << ",0";
        continue;
      }

      const map<string, unsigned>& smapNum = itcNum->second;
      auto itsNum = smapNum.find(s);
      if (itsNum == smapNum.end())
      {
        fout << ",0";
        continue;
      }

      const unsigned cDenom = itsDenom->second;
      const unsigned cNum = itsNum->second;

      fout << "," << fixed << setprecision(4) << 
        cNum / static_cast<float>(cDenom);
      sumDenom += cDenom;
      sumNum += cNum;

      catsumDenom[c] += cDenom;
      catsumNum[c] += cNum;
    }
    if (sumDenom == 0)
      fout << ",0\n";
    else
      fout << "," << fixed << setprecision(4) << 
        sumNum / static_cast<float>(sumDenom) << "\n";
  }

  fout << "Overall";
  for (auto &c: categories)
  {
    const unsigned cDenom = Words::lookup(catsumDenom, c);
    const unsigned cNum = Words::lookup(catsumNum, c);

    if (cDenom == 0 || cNum == 0)
      fout << ",0";
    else
      fout << "," << fixed << setprecision(4) <<
        cNum / static_cast<float>(cDenom);
  }

  fout << "\n";
}


void Words::printStatPercent(
  ofstream& fout,
  const string& heading,
  const CountMap& countDenom,
  const CountMap& countNum,
  const Format format) const
{
  if (format == PRON_FORMAT_TXT)
    Words::printStatPercentTXT(fout, heading, countDenom, countNum);
  else if (format == PRON_FORMAT_CSV)
    Words::printStatPercentCSV(fout, heading, countDenom, countNum);
}


void Words::printStats(
  const string& fname,
  const Format format) const
{
  ofstream fout;
  fout.open(fname);
  Words::printStat(fout, "Word counts", wordsCount, format);
  Words::printStat(fout, "Error counts", errorsCount1, format);
  Words::printStat(fout, "Error counts with alt", errorsCount2, format);

  Words::printStatPercent(fout, "Error ratios", wordsCount, 
    errorsCount1, format);
  Words::printStatPercent(fout, "Error ratios with alt", wordsCount, 
    errorsCount2, format);
  fout.close();
}


void Words::printMetapronError(
  ofstream& fout,
  const string& heading,
  const list<ErrorEntry>& errors) const
{
  fout << heading << "\n\n";

  for (auto &it: errors)
  {
    const ErrorEntry& ee = it;
    const WordEntry& we = words[ee.wordIndex];
    const PronEntry& le = we.prons[ee.listIndex];

    fout << "XX " << levenshtein(we.metapron, le.metaconv) << " ";
    fout << we.word << ": " << 
      setw(16) << left << we.metapron <<
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
  Words::printMetapronError(fout, "Errors primary", errors1);
  Words::printMetapronError(fout, "Errors with alt", errors2);
  fout.close();
}


void Words::printCollision(
  ofstream& fout,
  const string& heading,
  const StringIndexMap& collmap) const
{
  fout << heading << "\n\n";

  for (auto &it: collmap)
  {
    fout << "Metapron3: " << it.first << "\n";
    const set<unsigned>& cmap = it.second;

    for (auto &itc: cmap)
    {
      const WordEntry& we = words[itc];

      fout << "  " << we.word << ", " << we.metapron;
      if (we.metapronAlt != "")
        fout << ", " << we.metapronAlt;
      fout << ":";
      
      for (auto &itl: we.prons)
      {
        // if (itl.metaconv == it.first)
          fout << " " << itl.pron;
      }
      fout << "\n";
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

