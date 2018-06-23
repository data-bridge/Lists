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


const vector<vector<string>> PartsList =
{
  {"a", "&", "@", "A", "E", "eI", "I", "O", "oU", "U", "-", "E/@", "aI/j/eI", 
    "aI", "h/A", "j/@", "j/A"},
  {"aa", "&", "@", "A", "eI", "O", "oU"},
  {"aaiu", "aI/@"},
  {"ae", "&", "(@)", "@", "A", "aI", "E", "eI", "i"},
  {"aea", "i"},
  {"aeae", "i/i"},
  {"aeaea", "i/i/@"},
  {"aee", "i/i"},
  {"aei", "eI/I", "i/@", "i/aI", "i/I"},
  {"aejo", "aI/dZ/A"},
  {"aeju", "h/&/dZ/u"},
  {"aeo", "i/oU"},
  {"aeoe", "i/oU/E", "i/oU/I"},
  {"aeoi", "i/Oi"},
  {"aeu", "AU", "i/@"},
  {"aewi", "eI/w/aI"},
  {"aeye", "eI/@"},
  {"ai", "&", "@", "A", "aI", "E", "eI", "i", "j", "A/E"},
  {"aia", "aI/&", "eI/@", "eI/j", "A/j/@", "aI/@"},
  {"aiae", "eI/i", "eI/j/i"},
  {"aie", "aI/@", "aI/A", "aI/E", "aI/i"},
  {"aieu", "eI/j/u"},
  {"aio", "aI/j/A"},
  {"aj", "@/dZ", "eI", "A", "aI"},
  {"aja", "@/dZ/&", "@/dZ/@", "A/j/A", "A/h/A", "A/dZ/A", "@/j/@", "@/dZ/A"},
  {"aji", "A/dZ/i"},
  {"aju", "@/dZ/@"},
  {"ao", "eI/A", "A/oU", "AU"},
  {"au", "&", "@", "A", "AU", "eI", "O", "oU", "u"},
  {"aua", "A/w/A"},
  {"aw", "A", "O"},
  {"awayo", "A/w/A/j/oU"},
  {"awi", "A/w/i"},
  {"awo", "A/w/u"},
  {"ay", "aI", "E/@", "E", "eI", "eI/@"},
  {"aya", "A/j/@", "A/j/A", "eI/&", "eI/@", "h/aI/j/A", "h/aI/@"},
  {"aye", "A/j/E", "eI"},
  {"ayi", "A/j/I"},
  {"ayu", "A/j/u"},
  {"ayuo", "A/j/AU"},

  {"'b", "b"},
  {"b", "b"},
  {"bb", "b"},
  {"bc", "b/k", "b/s"},
  {"bcl", "b/k/l"},
  {"bbl", "b/l"},
  {"bd", "b/d"},
  {"bdd", "b/d"},
  {"bdr", "b/d/r"},
  {"bf", "b/f"},
  {"bfl", "b/f/l"},
  {"bfr", "b/f/r"},
  {"bg", "b/g", "b/dZ"},
  {"bh", "b"},
  {"bk", "b/k"},
  {"bl", "b/@/l", "b/l"},
  {"bm", "b/m"},
  {"bn", "b/@/n", "b/n"},
  {"bp", "b/p"},
  {"br", "b/r", "b/R"},
  {"bs", "b/s", "b/z"},
  {"bsc", "b/s", "b/s/k"},
  {"bscr", "b/s/k/r"},
  {"bsp", "b/s/p"},
  {"bst", "b/s/t"},
  {"bstr", "b/s/t/r"},
  {"bt", "b/t", "t"},
  {"btl", "t/-/l"},
  {"btr", "b/t/r"},
  {"bts", "p/t/s"},
  {"bv", "b/v"},
  {"bz", "b/z"},

  {"c", "k", "s", "S", "tS"},
  {"cb", "k/b"},
  {"cc", "k", "k/s", "tS"},
  {"cch", "k", "t/tS"},
  {"ch", "k", "h", "tS", "S"},
  {"ck", "k"},
  {"cl", "k/l"},
  {"ccl", "k/l"},
  {"ccr", "k/r"},
  {"cd", "k/d"},
  {"ch", "dZ", "k", "tS", "x"},
  {"chl", "k/l", "tS/l"},
  {"chm", "k/m", "x/m"},
  {"chn", "k/n", "S/n", "tS/n"},
  {"chp", "x/p"},
  {"chr", "k/r", "k/@/r", "k/R"},
  {"chs", "k/s"},
  {"chsh", "k/s", "x/S"},
  {"cht", "k/t", "s/t", "S/t", "t", "x/t"},
  {"ckb", "k/b"},
  {"ckl", "k/@/l", "k/l"},
  {"ckm", "k/m"},
  {"ckn", "k/n"},
  {"ckp", "k/p"},
  {"ckr", "k/r"},
  {"cks", "k/s"},
  {"ckv", "k/f"},
  {"cl", "k/@/l", "k/l"},
  {"cn", "k/n", "n"},
  {"cr", "k/r", "k/R"},
  {"cs", "k/s"},
  {"ct", "k/t", "k/tS", "k/S"},
  {"ctr", "k/t/r"},

  {"d", "d", "t", "dZ", "T"},
  {"db", "d/b"},
  {"dd", "d"},
  {"ddl", "d/-/l", "d/@/l", "d/l"},
  {"df", "d/f"},
  {"dg", "dZ", "d/g"},
  {"dh", "d", "d/h", "D"},
  {"dk", "d/k"},
  {"dl", "d/-/l", "d/@/l", "d/l"},
  {"dm", "d/m"},
  {"dn", "d/n"},
  {"dp", "d/p"},
  {"dr", "d/r", "d/@/r", "d/R"},
  {"ds", "d/s", "d/z"},
  {"dv", "d/v"},
  {"dz", "dZ", "d/z"},
  {"dzh", "dZ", "d/Z", "Z"},

  {"e", "eI", "I", "E", "@", "i", "-", ""},
  {"ea", "(@)", "&", "A", "E", "eI", "i", "j/@", "O", "i/@", "eI/A"},
  {"eau", "oU", "y"},
  {"ee", "i", "eI", "@", "E", "i/E"},
  {"eeuw", "u"},
  {"ei", "@", "aI", "E", "eI", "i", "I"},
  {"eo", "eI/oU", "i/@", "i/oU", "E/O"},
  {"eou", "@", "A", "AU", "i/@"},
  {"eu", "i/j/u"},
  {"ew", "h/j/u", "j/u", "u"},
  {"ewa", "eI/w/A"},
  {"eway", "w/eI"},
  {"ey", "eI", "i"},
  {"eye", "aI", "aI/@"},

  {"f", "f"},
  {"ff", "f"},
  {"ffl", "f/l", "f/@/l"},
  {"ffr", "f/r"},
  {"fgh", "f/g"},
  {"fl", "f/l"},
  {"fn", "f/n"},
  {"fr", "f/r", "f/R"},
  {"fs", "f/s"},
  {"ft", "f/t"},

  {"g", "g", "dZ", "Z"},
  {"gb", "g/b"},
  {"gg", "g", "dZ"},
  {"ggl", "g/-/l", "g/@/l", "g/l"},
  {"ggr", "g/r"},
  {"ggs", "g/z"},
  {"gh", "g", "x"},
  {"ght", "t"},
  {"ghtf", "t/f"},
  {"ghtl", "t/l"},
  {"gl", "g/l"},
  {"gm", "g/m", "m"},
  {"gn", "g/n", "n"},
  {"gr", "g/r"},

  {"h", "h", ""},
  {"hl", "l"},
  {"hm", "m"},
  {"hn", "n"},
  {"hnn", "n"},

  {"i", "i", "I", "@", "(@)", "aI", "E"},
  {"ia", "@", "i/&", "i/@", "i/A", "i", "j/A", "j/@", "aI/@"},
  {"iaye", "i", "aI/j/E"},
  {"ie", "i", "j/(@)", "aI"},
  {"ieu", "j/y"},
  {"iew", "j/u"},
  {"ii", "i"},
  {"io", "i/O", "i/oU", "j/@", "j/oU", "I/oU", "oU"},
  {"iou", "i/u"},
  {"iu", "@", "u", "j/u"},
  {"iwe", "i/w/eI"},

  {"j", "dZ/u"},
  {"ja", "&", "dZ/&", "dZ/A", "dZ/eI", "Z/A"},
  {"jai", "aI"},
  {"je", "dZ/@", "dZ/E", "j/eI", "i"},
  {"jea", "Z/A"},
  {"ji", "dZ/i", "dZ/I"},
  {"jiji", "dZ/I/dz/i"},
  {"jo", "dZ/A", "dZ/O", "dZ/oU", "h/O", "h/oU", "oU"},
  {"joo", "j/u"},
  {"ju", "dZ/U", "dZ/u"},
  {"juju", "dZ/u/dZ/u"},

  {"k", "k", "g", "tS"},
  {"kh", "k/h"},
  {"khl", "x/l"},
  {"kht", "x/t"},
  {"kk", "k"},
  {"kkr", "k/r"},
  {"kl", "k/l"},
  {"kn", "n", "k/n"},
  {"kp", "k/p"},
  {"kr", "k/r"},
  {"ks", "k/s"},
  {"kt", "k/t"},

  {"l", "l"},
  {"lb", "l/b"},
  {"lc", "l/k", "l/s", "l/S"},
  {"lch", "l/tS", "l/k"},
  {"ld", "l/d", "l/t"},
  {"ldb", "l/d/b"},
  {"ldf", "l/d/f"},
  {"ldl", "l/d/l"},
  {"ldr", "l/d/r"},
  {"lds", "l/d/z", "l/d/s"},
  {"ldt", "l/t"},
  {"ldv", "l/d/v"},
  {"lf", "l/f", "f"},
  {"lg", "l/dZ", "l/g"},
  {"lh", "l"},
  {"lk", "l/k"},
  {"lkh", "l/k", "k"},
  {"ll", "l"},
  {"llb", "l/b"},
  {"llf", "l/f"},
  {"llh", "l/h"},
  {"llm", "l/m"},
  {"llp", "l/p"},
  {"lls", "l/z"},
  {"lm", "l/m", "m"},
  {"ln", "l/n"},
  {"lp", "l/p"},
  {"lph", "l/f"},
  {"lr", "l/r"},
  {"ls", "l/s", "l/S"},
  {"lst", "l/s/t"},
  {"lt", "l/t"},
  {"ltl", "l/t/l"},
  {"ltr", "l/t/r"},
  {"lv", "l/v"},

  {"m", "m"},
  {"mb", "m/b", "m"},
  {"mbl", "m/b/@/l", "m/b/l"},
  {"mbr", "m/b/r"},
  {"m'b", "m/b"},
  {"md", "m/d"},
  {"mf", "m/f"},
  {"ml", "m/l"},
  {"mh", "m/h"},
  {"mm", "m"},
  {"mn", "m/n"},
  {"mp", "m/p"},
  {"mph", "m/f"},
  {"mpl", "m/p/l", "m/p/@/l"},
  {"mpr", "m/p/r"},
  {"mpt", "m/p/t"},
  {"mr", "m/r"},
  {"ms", "m/s", "m/z"},
  {"msh", "m/S"},
  {"mt", "m/t"},

  {"n", "n", "N"},
  {"nb", "n/b"},
  {"nc", "n/k"},
  {"nch", "n/tS"},
  {"ncl", "n/k/l"},
  {"ncr", "n/k/r"},
  {"nct", "n/k/S", "n/k/t"},
  {"nd", "n/d"},
  {"n'd", "n/dZ"},
  {"ndl", "n/d/-/l", "n/d/@/l", "n/d/l"},
  {"ndh", "n/t/h"},
  {"nddr", "n/d/r"},
  {"ndr", "n/d/r"},
  {"nf", "n/f"},
  {"nfl", "n/f/l"},
  {"nfr", "n/f/r"},
  {"ng", "n/dZ", "N/d", "N", "N/g", "n/g"},
  {"ngg", "N/g"},
  {"ngh", "N/g"},
  {"ngl", "N/g/@/l", "N/g/l", "N/l"},
  {"ngn", "N/n"},
  {"ngr", "n/g/r", "N/g/r"},
  {"ngs", "N/z", "N/s"},
  {"ngt", "N/t"},
  {"nh", "n/j"},
  {"nk", "N/k", "n/k"},
  {"nkl", "N/k/l", "N/k/@/l"},
  {"nkr", "n/k/r"},
  {"nl", "n/l"},
  {"nm", "n/m"},
  {"nn", "n"},
  {"np", "n/p"},
  {"npr", "n/p/r"},
  {"nr", "n/r", "n/R"},
  {"ns", "n/s", "n/z"},
  {"nsb", "n/z/b"},
  {"nsch", "n/S", "n/s"},
  {"nscr", "n/s/k/r", "n/s/k/R"},
  {"nsh", "n/S"},
  {"nsk", "n/s/k"},
  {"nsl", "n/s/l", "n/z/l"},
  {"nsp", "n/s/p"},
  {"nst", "n/s/t"},
  {"nstr", "n/s/t/r"},
  {"nt", "n/t", "N/t", "N"},
  {"n't", "n/t"},
  {"nth", "n/T"},
  {"nthr", "n/T/r"},
  {"ntl", "n/t/l"},
  {"ntr", "n/t/r"},
  {"nts", "n/t/s"},
  {"nv", "n/v"},
  {"nx", "N/k/s"},
  {"nz", "n/z"},

  {"o", "A", "oU", "O", "@", "u", "U"},
  {"oa", "oU/@"},
  {"oe", "oU", "U", "u"},
  {"oeu", "(@)", "i/@", "oU/i", "u", "y", "Y"},
  {"oi", "oU/i", "w/A", "Oi"},
  {"oji", "oU/dZ/I"},
  {"oo", "u", "oU"},
  {"ou", "u", "w/A", "AU", "@"},
  {"oua", "U/A", "u/A", "w/A"},
  {"oue", "w/@", "w/i"},
  {"ow", "AU", "oU"},
  {"owa", "U/w/A"},
  {"owe", "oU/@", "oU/w/E"},
  {"owo", "oU/w/A", "oU/w/oU"},
  {"oy", "Oi"},

  {"p", "p"},
  {"pb", "p/b", "b"},
  {"pch", "p/tS"},
  {"pf", "p/f", "f"},
  {"ph", "f", "p"},
  {"phr", "f/r"},
  {"pl", "p/l"},
  {"pn", "n"},
  {"pp", "p"},
  {"ppl", "p/l"},
  {"ppr", "p/r"},
  {"pr", "p/r"},
  {"ps", "p/s", "s"},
  {"pt", "p/S", "p/t"},

  {"q", "k"},

  {"r", "r", "R"},
  {"rb", "r/b"},
  {"rc", "r/k"},
  {"rch", "r/k", "R/S", "r/tS", "r/S"},
  {"rd", "r/d"},
  {"rf", "r/f"},
  {"rg", "r/g", "r"},
  {"rh", "r/h", "r"},
  {"rk", "r/k"},
  {"rl", "r/l", "R/l"},
  {"rm", "r/m"},
  {"rn", "r/n", "R/n"},
  {"rp", "r/p"},
  {"rph", "r/f"},
  {"rr", "r", "R"},
  {"rs", "r/s", "r/z"},
  {"rsd", "r/z/d"},
  {"rsp", "r/s/p"},
  {"rsr", "r/z/r"},
  {"rst", "r/s/t"},
  {"rt", "r/t", "R/t", "R"},
  {"rth", "r/T", "r/t"},
  {"rv", "r/v"},

  {"s", "s", "S", "z"},
  {"sb", "Z/b", "z/b"},
  {"sc", "s/k"},
  {"sch", "s/k"},
  {"scl", "s/k/l", "s/@/l"},
  {"scr", "s/k/r", "s/k/R"},
  {"sd", "s/d", "z/d"},
  {"sf", "s/f", "z/f"},
  {"sg", "s/g"},
  {"sh", "S"},
  {"shl", "S/l"},
  {"shn", "S/n"},
  {"shp", "S/p"},
  {"shr", "S/r"},
  {"shv", "S/f"},
  {"sk", "s/k"},
  {"sl", "s/l"},
  {"sm", "z/@/m", "s/m"},
  {"sn", "s/n"},
  {"sp", "s/p"},
  {"sph", "s/f"},
  {"spr", "s/p/r"},
  {"sq", "s/k"},
  {"sr", "s/r", "s/R", "z/r"},
  {"ss", "s"},
  {"ssl", "s/l"},
  {"ssm", "s/m"},
  {"ssn", "s/n"},
  {"ssp", "s/p"},
  {"st", "s/t"},
  {"sth", "s/T"},
  {"stl", "s/@/l", "s/t/l"},
  {"str", "s/t/r"},
  {"sv", "s/v", "z/v", "s/f"},

  {"t", "t", "S"},
  {"tb", "t/b"},
  {"tch", "tS"},
  {"tf", "t/f"},
  {"th", "T", "t"},
  {"thl", "t/l"},
  {"thr", "T/r"},
  {"tl", "t/l", "t/@/l", "t/-/l"},
  {"tm", "t/m"},
  {"tn", "t/n"},
  {"tp", "t/p"},
  {"tr", "t/r"},
  {"ts", "t/s"},
  {"tsh", "tS/A"},
  {"tsk", "t/s/k"},
  {"tt", "t"},
  {"ttl", "t/-/l", "t/l"},
  {"ttr", "t/r"},
  {"tv", "v"},
  {"tz", "t/s"},

  {"u", "u", "U", "@", "(@)", "Y", "j/u", "oU"},
  {"ua", "w/A", "w/eI", "u/A", "u/@", "u/E", "u/&", "w/@", "j/u/@"},
  {"ue", "u", "w/E", "w/eI", "E", ""},
  {"ui", "u", "w/I", "w/i", "Y", "j/u/I", "j/u/aI", "@", "aI", "i", "I"},
  {"uia", "i/@"},
  {"ujiji", "u/dZ/i/dZ/i"},
  {"uju", "u/Z/U"},
  {"uo", "j/u/A", "j/u/oU", "oU", "u/@", "u/A", "u/oU", "w/A", "w/O"},
  {"uuo", "u/@"},
  {"uwa", "U/w/A"},
  {"uwe", "u/w/E"},
  {"uwi", "u/w/i"},
  {"uy", "aI"},
  {"uya", "aI/&"},
  {"uyu", "u/j/u"},

  {"v", "v", "f"},
  {"vr", "v/@/r", "v/r", "v/R"},

  {"w", "w/I", "w/i", "w/E/@", "w/aI", "w/aI/@", "w/A", "w/@", "w/(@)"},
  {"wa", "w/O", "w/A"},
  {"way", "w/eI"},
  {"we", "w/i", "w/E", "w/eI", "w/@"},
  {"wee", "w/i"},
  {"wei", "w/i", "w/eI"},
  {"weu", "w/i/u"},
  {"wi", "w/I", "w/aI", "w/@", "w/(@)", "v/I", "v/I", "w/i"},
  {"wo", "w/oU"},
  {"woo", "w/U"},

  {"x", "z", "s", "S", "k/s"},
  {"xb", "k/s/b"},
  {"xc", "k/s/s", "k/s/k", "k/s"},
  {"xch", "k/s/tS"},
  {"xcl", "k/s/k/l"},
  {"xcr", "k/s/k/r"},
  {"xd", "k/s/d"},
  {"xf", "k/s/f"},
  {"xg", "k/s/g"},
  {"xgl", "k/s/g/l"},
  {"xh", "k/s/h", "k/s", "g/z"},
  {"xl", "k/s/l"},
  {"xm", "k/s/m"},
  {"xn", "k/s/n"},
  {"xp", "k/s/p"},
  {"xpl", "k/s/p/l"},
  {"xpr", "k/s/p/r"},
  {"xq", "k/s/k"},
  {"xr", "k/s/r"},
  {"xs", "k/s/s", "k/s"},
  {"xsc", "k/s"},
  {"xst", "k/s/s/t"},
  {"xt", "k/s/tS", "k/s/t"},
  {"xtb", "k/s/t/b"},
  {"xth", "k/s/T"},
  {"xthl", "k/s/T/l"},
  {"xtl", "k/s/t/l"},
  {"xtr", "k/s/t/r"},
  {"xv", "k/s"},

  {"y", "aI", "i", "I", "@", "-", "(@)"},
  {"ya", "j/@", "j/A", "j/&", "I/j/A", "i/A", "i/@", "aI/@", "aI/A", "aI/&"},
  {"yaou", "j/A/u"},
  {"ye", "j/@", "j/E", "i", "i/E", "i/(@)", "aI/I", "aI/i", "aI/@" },
  {"yi", "j/I", "j/aI", "i/I", "aI/I"},
  {"yo", "j/oU", "j/U", "j/@", "i/oU", "i/A", "i/O", "aI/A", "aI/@", "j/A"},
  {"you", "j/u"},
  {"yu", "i/@", "i/j/U", "i/u", "j/U", "j/u", "Y/u"},

  {"z", "z", "t/s", "T", "s", "Z"},
  {"zb", "z/b"},
  {"zc", "z/k", "z/dZ", "s/k"},
  {"zd", "z/d"},
  {"zg", "z/g"},
  {"zh", "Z", "dZ", "t/s"},
  {"zhd", "Z/d"},
  {"zl", "z/l", "z/@/l"},
  {"zm", "z/m"},
  {"zn", "s/n", "z/n"},
  {"zr", "z/R", "s/r"},
  {"zs", "Z"},
  {"zth", "z/T"},
  {"zv", "z/v", "t/s"},
  {"zz", "z", "tS", "t/s", "t/z", "d/z"},
  {"zzl", "z/l", "z/@/l"},
  {"zzm", "z/m"},

  {"'", ""}
};

const vector<string> Consonants =
{
  "b", "c", "d", "f", "g", "h", "k", "l", "m", 
  "n", "p", "q", "r", "s", "t", "v", "x", "z", "'"
};

const vector<string> Vowels =
{
  "a", "e", "i", "j", "o", "u", "w", "y"
};


Extract::Extract()
{
  Extract::reset();
  Extract::setTable();
}


Extract::~Extract()
{
}


void Extract::reset()
{
}


void Extract::setTable()
{
  for (unsigned i = 0; i < PartsList.size(); i++)
  {
    const auto& entry = PartsList[i];
    const string& part = entry[0];

    for (unsigned j = 1; j < entry.size(); j++)
      pronMap[part].push_back(entry[j]);
  }

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
      // Found a match.  Skip over '/' in pron.
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
        ret = recurse(word.substr(i), pron.substr(lpron+1), ! state);
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
  else 
  {
    const string& r = Extract::recurse(wlower, pron, isVowelMap[wlower.substr(0, 1)]);
    if (r != "")
      cout << r;
      // cout << "FAIL " << word << ", " << pron << ":\n" << r << "\n";
  }
}


void Extract::print(const string& fname) const
{
  ofstream fout;
  fout.open(fname);
  fout.close();
}

