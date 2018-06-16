/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/pron.h"

using namespace std;


vector<string> ORIG_TEST
{
  "iron",
  "witz",
  "",
  "Guillermo",
  "VILLASENOR",
  "GUILLERMINA",
  "PADILLA",
  "BJORK",
  "belle",
  "ERICH",
  "CROCE",
  "GLOWACKI",
  "hexagonality",
  "qing",
  "tsing",
  "Nicolas Gaydier"
};

vector<string> TEST
{
  "José",
  "Alexander",
  "Capucho"
};


void read_file(
  const string& fname,
  vector<string>& file_list);



int main(int argc, char * argv[])
{
  vector<string> file_list;
  vector<string>* test_list;
  string base;

  if (argc == 1)
    test_list = &ORIG_TEST;
  else if (argc == 2)
  {
    string fname = string(argv[1]);
    read_file(fname, file_list);

    test_list = &file_list;
  }
  else
  {
    cout << "Usage: test [input_file]\n";
    cout << "Writes to stdout";
    exit(0);
  }

  char word[80];
  char best[80];
  char alt[80];

  for (unsigned i = 0; i < (*test_list).size(); i++)
  {
    string w((*test_list)[i]);
    strcpy(word, w.c_str());
    metaword(word, true, true, best, alt);

    string b(best);
    string a(alt);

    cout << "Input " << w << endl;
    cout << "Best  " << b << endl;
    cout << "Alt   " << a << endl << endl;
  }
}


void read_file(
  const string& fname,
  vector<string>& file_list)
{
  const char * fn = fname.c_str();
  ifstream f(fn);
  if (! f.good())
  {
    cout << "File " << fname << " not found\n";
    exit(0);
  }

  string tmp;
  while (getline(f, tmp))
    file_list.push_back(tmp);
  f.close();
}

