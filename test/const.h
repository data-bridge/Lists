/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_CONSTANTS_H
#define PRON_CONSTANTS_H

#pragma warning(push)
#pragma warning(disable: 4365 4571 4625 4626 4774 5026 5027)
#include <string>
#include <vector>
#pragma warning(pop)

using namespace std;


// File formats.

enum Format
{
  PRON_FORMAT_TXT = 0,
  PRON_FORMAT_CSV = 1,
  PRON_FORMAT_SIZE = 2
};


const string FORMAT_NAMES[PRON_FORMAT_SIZE] =
{
  "TXT",
  "CSV"
};

// Input options.

struct FileOption
{
  bool setFlag;
  string name;
};

struct Options
{
  FileOption wordInput; // -w, --word
  FileOption phraseInput; // -p, --phrase
  FileOption fileInput; // -i, --infile
  FileOption dirInput; // -I, --indir

  bool vowelsFlag; // -v, --vowels
  bool exactFlag; // -e, --exact

  bool formatSetFlag; // -f, --format
  Format format;

  bool collisionsFlag; // -c, --collisions
};

#endif

