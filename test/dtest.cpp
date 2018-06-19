/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#include <iostream>
#include <iomanip>
#include <string>

#include "args.h"
#include "Words.h"
#include "Files.h"
#include "Timer.h"

#include "../include/pron.h"

using namespace std;


int main(int argc, char * argv[])
{
  Options options;
  readArgs(argc, argv, options);
  // printOptions(options);

  Words words;
  words.setEncoding(options.vowelsFlag, options.exactFlag);

  // Read inputs.
  Timer timer;
  timer.reset();
  timer.start();
  if (options.wordInput.setFlag)
  {
    char word[80];
    char best[80];
    char alt[80];

    strcpy(word, options.wordInput.name.c_str());
    metaword(word, options.vowelsFlag, options.exactFlag, best, alt);
    // TODO: Also get pron from command line.
    words.addReal(options.wordInput.name, "TODO:pron",
      "nocat", "nosub", "noline");
    words.addMeta(options.wordInput.name, string(best), string(alt));
    
  }
  else if (options.phraseInput.setFlag)
  {
    char phrase[80];
    char best[80];
    char alt[80];

    strcpy(phrase, options.phraseInput.name.c_str());
    metaword(phrase, options.vowelsFlag, options.exactFlag, best, alt);
    // TODO: Also get pron from command line.
    words.addReal(options.phraseInput.name, "TODO:pron",
      "nocat", "nosub", "noline");
    // TODO: Should actually do word by word, I think.
  }
  else if (options.fileInput.setFlag)
  {
    words.ingestFile(options.fileInput.name);
  }
  else if (options.dirInput.setFlag)
  {
    Files files;
    files.set(options);

    FileEntry ftask;
    while (files.next(ftask))
      words.ingestFile(ftask.fullName);
  }
  timer.stop();
  // TODO Put to timer.str()
  cout << setw(12) << left << "Reading" << 
    setw(10) << right << timer.str() << "\n";


  timer.reset();
  timer.start();
  char best[80];
  char alt[80];
  while (char const * w = words.next())
  {
    metaword(w, options.vowelsFlag, options.exactFlag, best, alt);
    words.addMeta(string(w), string(best), string(alt));
// cout << "Added " << string(w) << ", " <<
  // string(best) << ", " << string(alt) << endl;
  }
  timer.stop();
  cout << setw(12) << left << "Metapron" << 
    setw(10) << right << timer.str() << "\n";

  timer.reset();
  timer.start();
  words.findErrors();
  const string fout = "stats." + FORMAT_NAMES[options.format];
  words.printStats(fout, options.format);
  words.printMetapronErrors("errors.txt");
  timer.stop();
  cout << setw(12) << left << "Errors" << 
    setw(10) << right << timer.str() << "\n";



  if (options.collisionsFlag)
  {
    timer.reset();
    timer.start();
    words.findCollisions();
    words.printCollisions("collisions.txt");
    timer.stop();
    cout << setw(12) << left << "Collisions" << 
      setw(10) << right << timer.str() << "\n";
  }

}

