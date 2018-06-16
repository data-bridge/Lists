/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_ARGS_H
#define PRON_ARGS_H

#include "const.h"


void usage(const char base[]);

void printOptions(const Options& options);

void readArgs(
  int argc,
  char * argv[],
  Options& options);

#endif

