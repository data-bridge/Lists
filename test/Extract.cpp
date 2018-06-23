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
  {"ae", "&", "(@)", "@", "A", "aI", "E", "eI", "i", "aI/E"},
  {"aea", "i", "i/@"},
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
  {"ai", "&", "@", "A", "aI", "E", "eI", "i", "j", "A/E", "A/I", "A/i", "eI/I"},
  {"aia", "aI/&", "eI/@", "eI/j", "A/j/@", "aI/@"},
  {"aiae", "eI/i", "eI/j/i"},
  {"aie", "aI/@", "aI/A", "aI/E", "aI/i", "E"},
  {"aieu", "eI/j/u"},
  {"aio", "aI/j/A", "A/j/O"},
  {"aiu", "eI/@"},
  {"aiuo", "aI/w/oU"},
  {"aiwa", "aI/w/A"},
  {"aiwei", "aI/w/eI"},
  {"aiyu", "aI/j/u"},
  {"aiyua", "aI/j/Y/A"},
  {"aj", "@/dZ", "eI", "A", "aI", "&/dZ"},
  {"aja", "@/dZ/&", "@/dZ/@", "A/j/A", "A/h/A", "A/dZ/A", "@/j/@", "@/dZ/A", "aI/@"},
  {"ajaa", "A/j/A"},
  {"ajai", "@/Z/@"},
  {"aje", "&/dZ/@", "&/dZ/I", "@/dZ/E", "A/dZ/@", "A/dZ/E"},
  {"ajee", "A/dZ/i", "@/dZ/i"},
  {"ajeu", "A/Z/y"},
  {"aji", "A/dZ/i", "@/dZ/i", "&/dZ/i"},
  {"ajj", "&/dZ"},
  {"ajji", "&/dZ/i"},
  {"ajo", "@/dZ/@", "@/dZ/A", "@/dZ/O", "@/dz/oU", "@/h/oU", "@/j/oU", "@/Z/O",
    "A/h/O", "A/h/oU", "A/j/O", "eI/dZ/@", "eI/oU"},
  {"ajoie", "&/z/w/A"},
  {"ajou", "@/dZ/u"},
  {"aju", "@/dZ/@", "A/Z/U"},
  {"ajua", "A/w/A"},
  {"ajuo", "aI/w/oU"},
  {"ajuwo", "A/Z/U/w/A"},
  {"ao", "eI/A", "A/oU", "AU", "A/O", "eI/oU", "O", "i/oU"},
  {"aoa", "A/w/A", "AU/A"},
  {"aoe", "eI/i"},
  {"aoi", "AU/I", "eI/i", "eI/I", "i"},
  {"aou", "A/u"},
  {"aoue", "A/w/@"},
  {"aoui", "A/w/i", "O/i"},
  {"au", "&", "@", "A", "AU", "eI", "O", "oU", "u", "A/u"},
  {"aua", "A/w/A"},
  {"aue", "AU/@", "AU"},
  {"auea", "@/w/eI/@"},
  {"auai", "O/aI"},
  {"aui", "AU/i"},
  {"auja", "O/dZ/A"},
  {"aw", "A", "O"},
  {"awa", "A/w/A", "@/v/A", "@/w/O", "AU/w/@"},
  {"awai", "@/w/eI", "A/w/I"},
  {"awaii", "@/w/aI/i"},
  {"awaiia", "@/w/aI/@"},
  {"away", "@/w/eI"},
  {"awayo", "A/w/A/j/oU"},
  {"awe", "O"},
  {"awea", "@/w/E", "@/w/i"},
  {"awee", "O/i"},
  {"awei", "@/w/eI"},
  {"awi", "A/w/i"},
  {"awie", "Oi"},
  {"awo", "A/w/u"},
  {"awy", "A/w/i"},
  {"ay", "aI", "E/@", "E", "eI", "eI/@", "i"},
  {"aya", "A/j/@", "A/j/A", "eI/&", "eI/@", "aI/@", "aI/j/A", "@/j/A", "aI/A", 
    "j/@", "eI/j/@"},
  {"aye", "A/j/E", "eI", "A/i", "@/j/eI"},
  {"ayi", "A/j/I", "A/j/i"},
  {"ayo", "A/j/A", "A/j/O", "A/j/oU", "aI/oU", "eI/@", "eI/A", "eI/j/oU", "eI/O",
    "eI/oU"},
  {"ayu", "A/j/u"},
  {"ayuo", "A/j/AU"},
  {"ayya", "aI/j/&"},

  {"'b", "b"},
  {"b'", "b"},
  {"b", "b", "p"},
  {"bb", "b"},
  {"bbr", "b/r"},
  {"bbs", "b/z"},
  {"bc", "b/k", "b/s"},
  {"bch", "b/tS"},
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
  {"bkh", "b/k", "b/x"},
  {"bkn", "p/k/n"},
  {"bl", "b/@/l", "b/l"},
  {"bm", "b/m"},
  {"bmh", "b/m"},
  {"bn", "b/@/n", "b/n"},
  {"b'n", "b/-/n"},
  {"bp", "b/p"},
  {"bpl", "b/p/l"},
  {"bq", "b/k"},
  {"br'", "b/r"},
  {"b'r", "b/r"},
  {"br", "b/r", "b/R"},
  {"brn", "b/(@)/r/n"},
  {"brz", "b/r/E/Z", "b/r/i/z", "b/Z"},
  {"b's", "b/z"},
  {"bs", "b/s", "b/z"},
  {"bsc", "b/s", "b/s/k"},
  {"bscr", "b/s/k/r"},
  {"bsh", "S/i", "S/aI"},
  {"bsk", "p/s/k"},
  {"bsl", "b/s/l"},
  {"bsp", "b/s/p"},
  {"bst", "b/s/t"},
  {"bstr", "b/s/t/r"},
  {"bt", "b/t", "t"},
  {"btf", "t/f"},
  {"btl", "t/-/l"},
  {"btr", "b/t/r"},
  {"bts", "p/t/s"},
  {"bv", "b/v"},
  {"bz", "b/z"},

  {"c", "k", "s", "S", "tS"},
  {"cb", "k/b"},
  {"cc", "k", "k/s", "tS"},
  {"cch", "k", "t/tS"},
  {"cf", "k/f"},
  {"cfl", "k/f/l"},
  {"ch", "k", "h", "tS", "S"},
  {"ck", "k"},
  {"cl", "k/l"},
  {"ccl", "k/l"},
  {"ccr", "k/r"},
  {"cd", "k/d"},
  {"ch'", "tS"},
  {"ch", "dZ", "k", "tS", "x"},
  {"chb", "tS/b"},
  {"chbl", "tS/b/l"},
  {"chc", "tS/k"},
  {"chch", "k/tS", "tS"},
  {"chcl", "tS/k/l"},
  {"chcr", "tS/k/r"},
  {"chd", "tS/d"},
  {"chdr", "tS/d/r"},
  {"chf", "tS/f"},
  {"chh", "k/h", "tS/h"},
  {"chk", "tS/k", "s/k"},
  {"chl", "k/l", "tS/l"},
  {"chm", "k/m", "x/m", "m"},
  {"chn", "k/n", "S/n", "tS/n"},
  {"chp", "x/p"},
  {"chr", "k/r", "k/@/r", "k/R"},
  {"chs", "k/s"},
  {"chsb", "k/s/b"},
  {"chsh", "k/s", "x/S"},
  {"chst", "k/s/t", "tS/s/t"},
  {"cht", "k/t", "s/t", "S/t", "t", "x/t"},
  {"chth", "k/T", "T", "x/t/h"},
  {"chtl", "tS/t/l"},
  {"chtp", "x/t/p"},
  {"chts", "t/s"},
  {"chz", "x/z"},
  {"ckb", "k/b"},
  {"ckbl", "k/b/l"},
  {"ckbr", "k/b/r"},
  {"ckc", "k/k", "k"},
  {"ckd", "k/d"},
  {"ckdr", "k/d/r"},
  {"ckf", "k/f"},
  {"ckfl", "k/f/l"},
  {"ckfr", "k/f/r"},
  {"ckg", "k/g"},
  {"ckgr", "k/g/r"},
  {"ckh", "k", "k/h"},
  {"ckk", "k/k"},
  {"ckkn", "k/n"},
  {"ckl", "k/@/l", "k/l"},
  {"ckm", "k/m"},
  {"ckn", "k/n"},
  {"ckp", "k/p"},
  {"ckpl", "k/p/l"},
  {"ckpr", "k/p/r"},
  {"ckr", "k/r"},
  {"ck's", "k/s"},
  {"cks", "k/s"},
  {"cksb", "k/s/b"},
  {"cksc", "k/s/k"},
  {"cksm", "k/s/m"},
  {"cksn", "k/s/n"},
  {"cksp", "k/s/p"},
  {"ckspl", "k/s/p/l"},
  {"ckst", "k/s/t"},
  {"ckstr", "k/s/t/r"},
  {"ckt", "k/t"},
  {"cktg", "k/T"},
  {"ckv", "k/f"},
  {"cl", "k/@/l", "k/l"},
  {"cm", "k/m"},
  {"cn", "k/n", "n"},
  {"cph", "k/f"},
  {"cq", "k"},
  {"cr", "k/r", "k/R"},
  {"cs", "k/s"},
  {"ct", "k/t", "k/tS", "k/S"},
  {"ctr", "k/t/r"},
  {"cz", "tS", "z"},

  {"'d", "d"},
  {"d'", "d"},
  {"d", "d", "t", "dZ", "T", ""},
  {"db", "d/b"},
  {"dc", "d/k"},
  {"dd", "d"},
  {"ddh", "d"},
  {"ddl", "d/-/l", "d/@/l", "d/l"},
  {"ddr", "d/r"},
  {"dds", "d/s", "d/z"},
  {"df", "d/f"},
  {"dfl", "d/f/l"},
  {"dfr", "d/f/r"},
  {"dg", "dZ", "d/g"},
  {"dgr", "d/g/r"},
  {"dh", "d", "d/h", "D"},
  {"d'h", "d"},
  {"dhr", "d/r", "d/R"},
  {"dk", "d/k"},
  {"dl", "d/-/l", "d/@/l", "d/l"},
  {"dm", "d/m"},
  {"dn", "d/n"},
  {"dp", "d/p"},
  {"dr", "d/r", "d/@/r", "d/R"},
  {"ds", "d/s", "d/z"},
  {"dsl", "d/s/l"},
  {"dsm", "d/z/m"},
  {"dsp", "d/s/p"},
  {"dspr", "d/s/p/r"},
  {"dst", "d/s/t"},
  {"dstr", "d/s/t/r"},
  {"dt", "d/t"},
  {"dth", "d/T", "t/h"},
  {"dv", "d/v"},
  {"dz", "dZ", "d/z"},
  {"dzh", "dZ", "d/Z", "Z"},

  {"e", "eI", "I", "E", "@", "i", "-", ""},
  {"ea", "(@)", "&", "A", "E", "eI", "i", "j/@", "O", "i/@", "eI/A"},
  {"eau", "oU", "y"},
  {"ee", "i", "eI", "@", "E", "i/E"},
  {"eeuw", "u"},
  {"ej", "E/dZ"},
  {"eja", "i/dZ/&"},
  {"eji", "E/dZ/i", "I/dZ/aI"},
  {"ei", "@", "aI", "E", "eI", "i", "I"},
  {"eo", "eI/oU", "i/@", "i/oU", "E/O"},
  {"eou", "@", "A", "AU", "i/@"},
  {"eu", "i/j/u"},
  {"ew", "h/j/u", "j/u", "u"},
  {"ewa", "eI/w/A"},
  {"eway", "w/eI"},
  {"ewi", "eI/w/i", "i/w/aI", "I/w/I", "i/w/I", "j/u/I", "u/I"},
  {"ey", "eI", "i"},
  {"eye", "aI", "aI/@"},

  {"'f", "f"},
  {"f", "f", "v"},
  {"fb", "f/b"},
  {"fc", "f/k"},
  {"fd", "f/d", "f/t"},
  {"ff", "f"},
  {"ffb", "f/b"},
  {"ffc", "f/k"},
  {"ffh", "f/h"},
  {"ffk", "f/k"},
  {"ffl", "f/l", "f/@/l"},
  {"ffm", "f/m"},
  {"ffn", "f/n"},
  {"ffpr", "f/p/r"},
  {"ffr", "f/r"},
  {"ffs", "f/s"},
  {"ffsh", "f/S"},
  {"fft", "f/t"},
  {"fg", "f/g"},
  {"fgh", "f/g"},
  {"fk", "f/k"},
  {"fl", "f/l"},
  {"fm", "f/m"},
  {"fn", "f/n"},
  {"fr", "f/r", "f/R"},
  {"fs", "f/s"},
  {"fsk", "f/s/k"},
  {"fss", "f/s"},
  {"fst", "f/s/t"},
  {"ft", "f/t"},
  {"ftb", "f/t/b"},
  {"ftf", "f/t/f"},
  {"ftl", "f/t/l"},
  {"ftm", "f/t/m"},
  {"ftp", "f/t/p"},
  {"fts", "f/t/s"},

  {"g", "g", "dZ", "Z", "g/j"},
  {"gb", "g/b"},
  {"gc", "dZ"},
  {"gd", "g/d"},
  {"gf", "g/f"},
  {"gfl", "g/f/l"},
  {"gg", "g", "dZ"},
  {"ggb", "g/b"},
  {"ggc", "g/k"},
  {"ggcr", "g/k/r"},
  {"ggdr", "g/d/r"},
  {"ggl", "g/-/l", "g/@/l", "g/l"},
  {"ggpl", "g/p/l"},
  {"ggr", "g/r"},
  {"ggs", "g/z"},
  {"ggsh", "g/S"},
  {"gh", "g", "x"},
  {"ghd", "g/d"},
  {"ghl", "g/l"},
  {"ght", "t"},
  {"ghtf", "t/f"},
  {"ghtl", "t/l"},
  {"gl", "g/l"},
  {"gm", "g/m", "m"},
  {"gn", "g/n", "n"},
  {"gr", "g/r"},

  {"h", "h", ""},
  {"hd", "d"},
  {"hg", "r"},
  {"hl", "l"},
  {"hm", "m"},
  {"hn", "n"},
  {"hnn", "n"},
  {"hr", "r", "R"},
  {"hz", "z"},

  {"i", "i", "I", "@", "(@)", "aI", "E"},
  {"ia", "@", "i/&", "i/@", "i/A", "i", "j/A", "j/@", "aI/@", "j/U"},
  {"iaye", "i", "aI/j/E"},
  {"ie", "i", "j/(@)", "aI"},
  {"ieu", "j/y"},
  {"iew", "j/u"},
  {"ii", "i"},
  {"io", "i/O", "i/oU", "j/@", "j/oU", "I/oU", "oU"},
  {"iou", "i/u"},
  {"iu", "@", "u", "j/u"},
  {"iwe", "i/w/eI"},
  {"iwiye", "i/w/i/j/@"},
  {"iya", "i/j/&", "i/j/@", "i/j/A", "i/j/O"},
  {"iyaa", "i/j/A"},
  {"iye", "i/@"},

  {"j", "dZ/u"},
  {"ja", "&", "dZ/&", "dZ/A", "dZ/eI", "Z/A"},
  {"jaa", "dZ/@"},
  {"jai", "aI"},
  {"je", "dZ/@", "dZ/E", "j/eI", "i"},
  {"jea", "Z/A"},
  {"ji", "dZ/i", "dZ/I"},
  {"jiji", "dZ/I/dz/i"},
  {"jo", "dZ/A", "dZ/O", "dZ/oU", "h/O", "h/oU", "oU"},
  {"joo", "j/u"},
  {"ju", "dZ/U", "dZ/u"},
  {"juju", "dZ/u/dZ/u"},
  {"jwa", "i/w/A"},

  {"k", "k", "g", "tS"},
  {"kd", "k/d"},
  {"kf", "k/f"},
  {"kh", "k/h", "k"},
  {"khl", "x/l"},
  {"kht", "x/t"},
  {"kk", "k"},
  {"kkr", "k/r"},
  {"kl", "k/l"},
  {"kn", "n", "k/n"},
  {"kp", "k/p"},
  {"kr", "k/r", "k/@/r"},
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
  {"lq", "l/k"},
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
  {"mc", "m/s"},
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

  {"n", "n", "N", "n/j"},
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
  {"ndv", "n/d/w"},
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
  {"ngz", "N/z"},
  {"nh", "n/j", "N"},
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

  {"o", "A", "oU", "O", "@", "u", "U", "j/oU", "y"},
  {"oa", "oU/@", "oU/A", "oU", "O/A", "w/A", "oU/&"},
  {"oe", "oU", "U", "u"},
  {"oeu", "(@)", "i/@", "oU/i", "u", "y", "Y"},
  {"oi", "oU/i", "w/A", "Oi"},
  {"oia", "O/j/A", "Oi/@", "Oi/A", "oU/aI"},
  {"oji", "oU/dZ/I"},
  {"oo", "u", "oU"},
  {"ou", "u", "w/A", "AU", "@"},
  {"oua", "U/A", "u/A", "w/A"},
  {"oue", "w/@", "w/i"},
  {"oui", "u/I", "u/i"},
  {"ouj", "u/dZ"},
  {"ow", "AU", "oU"},
  {"owa", "U/w/A"},
  {"owe", "oU/@", "oU/w/E", "A/w", "AU", "oU"},
  {"owo", "oU/w/A", "oU/w/oU"},
  {"oy", "Oi", "y/i"},
  {"oya", "Oi/@", "Oi/A", "O/j/A", "Oi/&", "w/A/j/A", "oU/j/A"},
  {"oyu", "O/j/u", "oU/j/u"},

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
  {"qb", "k/b"},
  {"qs", "k/s"},

  {"r", "r", "R"},
  {"rb", "r/b"},
  {"rc", "r/k", "R/k"},
  {"rch", "r/k", "R/S", "r/tS", "r/S"},
  {"rd", "r/d", "R"},
  {"rf", "r/f"},
  {"rg", "r/g", "r"},
  {"rgh", "r/g"},
  {"rh", "r/h", "r"},
  {"rk", "r/k"},
  {"rl", "r/l", "R/l"},
  {"rm", "r/m"},
  {"rn", "r/n", "R/n"},
  {"rp", "r/p"},
  {"rph", "r/f"},
  {"rpl", "r/p/l"},
  {"rpr", "r/p/r"},
  {"rps", "r/p/s"},
  {"rq", "r/k"},
  {"rr", "r", "R"},
  {"rrh", "r"},
  {"rs", "r/s", "r/z", "R/s"},
  {"rsd", "r/z/d"},
  {"rsh", "r/S"},
  {"rsk", "r/s/k", "R/s/k"},
  {"rsp", "r/s/p"},
  {"rsr", "r/z/r"},
  {"rst", "r/s/t"},
  {"rt", "r/t", "R/t", "R"},
  {"rtf", "r/t/f"},
  {"rth", "r/T", "r/t"},
  {"rthn", "r/T/n"},
  {"rthp", "r/T/p"},
  {"rthr", "r/T/r"},
  {"rtl", "r/t/l", "r/t/-/l"},
  {"rv", "r/v"},
  {"rz", "r/s", "r/z"},

  {"'s", "z"},
  {"s'", "z"},
  {"s", "s", "S", "z", "Z", ""},
  {"sb", "Z/b", "z/b"},
  {"sbr", "s/b/r", "z/b/r"},
  {"sc", "s/k"},
  {"sch", "s/k", "S"},
  {"schb", "S/b"},
  {"schk", "S/k"},
  {"schl", "S/l"},
  {"schm", "S/m"},
  {"schn", "S/n"},
  {"schr", "s/k/r", "S/r", "S/R"},
  {"schsch", "S/k"},
  {"schv", "S/v"},
  {"scl", "s/k/l", "s/@/l"},
  {"scr", "s/k/r", "s/k/R"},
  {"sd", "s/d", "z/d"},
  {"sdr", "s/d/r", "z/d/r"},
  {"sf", "s/f", "z/f"},
  {"sfl", "s/f/l", "z/f/l"},
  {"sfr", "s/f/r"},
  {"sg", "s/g"},
  {"sgl", "s/g/l"},
  {"sgn", "s/n"},
  {"sgr", "s/g/r", "s/k/r", "z/d/r"},
  {"sh", "S"},
  {"shb", "S/b"},
  {"shc", "S/k"},
  {"shd", "S/t"},
  {"shf", "S/f"},
  {"shg", "S/g"},
  {"shh", "S/h", "S"},
  {"shk", "S/k"},
  {"shl", "S/l"},
  {"shm", "S/m"},
  {"shn", "S/n"},
  {"shp", "S/p"},
  {"shr", "S/r"},
  {"sht", "S/t"},
  {"shv", "S/f"},
  {"sk", "s/k"},
  {"skh", "s/k"},
  {"skm", "s/k/m"},
  {"skn", "s/n"},
  {"skr", "s/k/r", "s/k/@/R"},
  {"skt", "s/k/t"},
  {"skv", "s/k/v"},
  {"sl", "s/l"},
  {"sm", "z/@/m", "s/m"},
  {"sn", "s/n"},
  {"sp", "s/p"},
  {"sph", "s/f"},
  {"spl", "s/p/l"},
  {"spn", "s/p/n"},
  {"spr", "s/p/r"},
  {"spt", "s/p/t"},
  {"sq", "s/k"},
  {"sr", "s/r", "s/R", "z/r"},
  {"srh", "s/r"},
  {"ss", "s"},
  {"ssb", "s/b"},
  {"ssbl", "s/b/l"},
  {"ssc", "s/k"},
  {"ssh", "s/h", "S"},
  {"ssk", "s/k"},
  {"ssl", "s/l"},
  {"ssm", "s/m"},
  {"ssn", "s/n"},
  {"ssp", "s/p"},
  {"ssr", "s/r"},
  {"sst", "s/t"},
  {"st", "s/t"},
  {"stb", "s/t/b"},
  {"stc", "s/t/k"},
  {"stf", "s/t/f"},
  {"sth", "s/T"},
  {"sthm", "s/m", "z/m"},
  {"stl", "s/@/l", "s/t/l"},
  {"stm", "s/t/m"},
  {"stn", "s/t/n"},
  {"str", "s/t/r"},
  {"stv", "s/t/v"},
  {"sv", "s/v", "z/v", "s/f"},
  {"sz", "z", "S", "s"},
  {"szk", "S/k", "s/k"},
  {"szt", "s/t"},

  {"t", "t", "S", ""},
  {"tb", "t/b", "t/@/b", "t/i/b"},
  {"tc", "t/k"},
  {"tch", "tS"},
  {"tchd", "tS/d"},
  {"tchf", "tS/f"},
  {"tchl", "tS/l"},
  {"tchm", "tS/m"},
  {"tchp", "tS/p"},
  {"tchst", "tS/s/t"},
  {"tcl", "t/k/l"},
  {"tcr", "t/k/r"},
  {"td", "t/d"},
  {"tdr", "t/d/r"},
  {"tf", "t/f"},
  {"tfl", "t/f/l"},
  {"tfr", "t/f/r"},
  {"tg", "t/g"},
  {"tgr", "t/g/r", "t/dZ"},
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
  {"ui", "u", "w/I", "w/i", "Y", "j/u/I", "j/u/aI", "@", "aI", "i", "I", "u/i"},
  {"uia", "i/@"},
  {"uja", "u/Z/A"},
  {"ujiji", "u/dZ/i/dZ/i"},
  {"uju", "u/Z/U"},
  {"uo", "j/u/A", "j/u/oU", "oU", "u/@", "u/A", "u/oU", "w/A", "w/O"},
  {"uuo", "u/@"},
  {"uwa", "U/w/A"},
  {"uwai", "U/w/eI"},
  {"uwe", "u/w/E"},
  {"uwi", "u/w/i"},
  {"uwia", "u/i/@"},
  {"uy", "aI"},
  {"uya", "aI/&"},
  {"uyu", "u/j/u"},

  {"v", "v", "f"},
  {"'v", "v"},
  {"vc", "v/t/s"},
  {"vd", "b/d", "v/d"},
  {"vg", "v/g"},
  {"vgr", "f/g/r"},
  {"vk", "f/k", "v/k"},
  {"vl", "v/l"},
  {"vlt", "v/-/l/t"},
  {"vn", "v/n"},
  {"vp", "f/p"},
  {"vr", "v/@/r", "v/r", "v/R"},
  {"vrd", "v/r/@/d"},
  {"vsk", "v/s/k", "f/s/k"},
  {"vst", "v/i/s/t"},
  {"vt", "v/t", "v/i/t", "f/t"},
  {"vtz", "f/t/s"},
  {"vv", "v"},
  {"vz", "v/z"},
  {"vzh", "v/Z"},

  {"w", "w/I", "w/i", "w/E/@", "w/aI", "w/aI/@", "w/A", "w/@", "w/(@)"},
  {"wa", "w/O", "w/A", "w/@", "w/eI"},
  {"waa", "v/a", "w/&", "w/O"},
  {"wae", "w/eI"},
  {"wai", "w/A/i", "w/aI", "w/E", "w/eI"},
  {"wau", "w/A", "w/O"},
  {"waw", "w/A", "w/AU"},
  {"way", "w/eI"},
  {"we", "w/i", "w/E", "w/eI", "w/@"},
  {"wea", "w/E/@", "w/E", "w/i"},
  {"wee", "w/i"},
  {"wei", "w/i", "w/eI"},
  {"weu", "w/i/u"},
  {"wey", "v/aI", "v/eI", "w/eI"},
  {"wi", "w/I", "w/aI", "w/@", "w/(@)", "v/I", "v/I", "w/i"},
  {"wia", "w/i/j/A"},
  {"wie", "v/aI", "v/i", "w/aI", "w/i"},
  {"wo", "w/oU"},
  {"woe", "w/oU", "v/@"},
  {"woo", "w/U", "w/oU"},
  {"wou", "w/AU", "w/oU", "w/U", "w/u"},
  {"wu", "w/u/A", "w/@", "v/U", "w/(@)", "w/u", "w/U"},
  {"wy", "w/aI", "w/I"},
  {"wya", "w/aI/@"},
  {"wye", "w/aI", "w/aI/@"},
  {"wyo", "w/aI/oU"},

  {"x", "z", "s", "S", "k/s", ""},
  {"xb", "k/s/b"},
  {"xbl", "k/s/b/l"},
  {"xbr", "k/s/b/r"},
  {"xc", "k/s/s", "k/s/k", "k/s"},
  {"xch", "k/s/tS"},
  {"xcl", "k/s/k/l"},
  {"xcr", "k/s/k/r"},
  {"xd", "k/s/d"},
  {"xf", "k/s/f"},
  {"xg", "k/s/g"},
  {"xgl", "k/s/g/l"},
  {"xgr", "k/s/g/r"},
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

  {"y", "aI", "i", "I", "@", "-", "(@)", "j/i"},
  {"ya", "j/@", "j/A", "j/&", "I/j/A", "i/A", "i/@", "aI/@", "aI/A", "aI/&", "j/E"},
  {"yae", "aI/i", "h/aI/i", "j/i"},
  {"yaeu", "aI/i"},
  {"yai", "aI", "j/Oi"},
  {"yaju", "j/@"},
  {"yao", "j/O"},
  {"yaou", "j/A/u"},
  {"yau", "j/O", "i/O", "j/AU", "j/oU"},
  {"yaw", "j/O"},
  {"ye", "j/@", "j/E", "i", "i/E", "i/(@)", "aI/I", "aI/i", "aI/@", "aI"},
  {"yi", "j/I", "j/aI", "i/I", "aI/I"},
  {"yo", "j/oU", "j/U", "j/@", "i/oU", "i/A", "i/O", "aI/A", "aI/@", "j/A"},
  {"you", "j/u"},
  {"yu", "i/@", "i/j/U", "i/u", "j/U", "j/u", "Y/u"},

  {"z", "z", "t/s", "T", "s", "Z"},
  {"zb", "z/b"},
  {"zc", "z/k", "z/dZ", "s/k"},
  {"zd", "z/d"},
  {"zf", "z/f"},
  {"zg", "z/g"},
  {"zh", "Z", "dZ", "t/s", "S"},
  {"zhd", "Z/d"},
  {"zhk", "Z/k"},
  {"zhn", "Z/n"},
  {"zk", "z/k", "s/k"},
  {"zl", "z/l", "z/@/l"},
  {"zm", "z/m"},
  {"zn", "s/n", "z/n"},
  {"zp", "z/p"},
  {"zr", "z/R", "s/r"},
  {"zs", "Z"},
  {"zsv", "Z/v"},
  {"zt", "z/t"},
  {"zth", "z/T"},
  {"zv", "z/v", "t/s"},
  {"zz", "z", "tS", "t/s", "t/z", "d/z"},
  {"zzb", "z/b"},
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

