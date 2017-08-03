// Test driver for Metaphone3 port.

#include <iostream>
#include <fstream>
#include <vector>

#include "Metaphone3.h"

#define UNUSED(x) ((void)(true ? 0 : ((x), void(), 0)))

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


void tokenize(
  const string& text,
  vector<string>& tokens,
  const string& delimiters);

void read_file(
  const string& fname,
  vector<string>& file_list);



int main(int argc, char * argv[])
{
  vector<string> file_list;
  vector<string>* test_list;
  string base;

  if (argc == 1)
    test_list = &TEST;
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


  Metaphone3 mph;
  for (auto &wd: * test_list)
  {
    cout << wd << ";";
    vector<string> tokens;
    tokens.clear();
    tokenize(wd, tokens, " ");

    for (bool encodeVowels: {false, true})
    {
      mph.setEncodeVowels(encodeVowels);
      for (bool encodeExact: {false, true})
      {
        mph.setEncodeExact(encodeExact);

        string main, alt;
        for (auto &t: tokens)
        {
          mph.setWord(t);
          mph.encode();

          string x = mph.getMetaph();
          if (x != "")
            main += x + " ";
          x = mph.getAlternateMetaph();
          if (x != "")
            alt += x + " ";
        }
        if (main != "")
          main.pop_back(); // Drop trailing space
        if (alt != "")
        alt.pop_back();
        cout << main << ";" << alt << ";";
      }
    }
    cout << endl;
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

