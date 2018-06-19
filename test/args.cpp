/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

// These functions parse the command line for options.


#pragma warning(push)
#pragma warning(disable: 4365 4571 4625 4626 4774 5026 5027)
#include <iostream>
#include <iomanip>
#include <string>
#pragma warning(pop)

#include "args.h"

using namespace std;


struct OptEntry
{
  string shortName;
  string longName;
  unsigned numArgs;
};

#define PRON_NUM_OPTIONS 8

static const OptEntry OPT_LIST[PRON_NUM_OPTIONS] =
{
  {"w", "word", 1},
  {"p", "phrase", 1},
  {"i", "infile", 1},
  {"I", "indir", 1},
  {"v", "vowels", 0},
  {"e", "exact", 0},
  {"f", "format", 1},
  {"c", "collisions", 0}
};

static string shortOptsAll, shortOptsWithArg;

static int getNextArgToken(
  int argc,
  char * argv[]);

static void setDefaults();

static void printFileOption(
  const FileOption& fopt,
  const string& text);

static void printBinaryOption(
  const bool flag,
  const string& text);

static void checkArgs(const Options& options);


void usage(
  const char base[])
{
  string basename(base);
  const size_t l = basename.find_last_of("\\/");
  if (l != string::npos)
    basename.erase(0, l+1);

  cout <<
    "Usage: " << basename << " [options]\n\n" <<
    "-w, --word s       Input word.\n\n" <<
    "-p, --phrase s     Phrase (in quotes).\n\n" <<
    "-i, --infile s     Input file.\n\n" <<
    "-I, --indir s      Input directory.  Read all eligible files.\n" <<
    "\n" <<
    "-v, --vowels       Enable vowels in output.\n" <<
    "                   (Default: not set)\n\n" <<
    "-e, --exact        Enable output.\n" <<
    "                   (Default: not set)\n\n" <<
    "-f, --format s     Output format (default: txt).\n" <<
    "                   Values TXT, CSV.\n\n" <<
    "-c, --collisions   Output specific collisions.\n" <<
    "                   (Default: not set)\n\n" <<
    endl;
}


static int nextToken = 1;
static string optarg;

static int getNextArgToken(
  int argc,
  char * argv[])
{
  // 0 means done, -1 means error.

  if (nextToken >= argc)
    return 0;

  string str(argv[nextToken]);
  if (str[0] != '-' || str.size() == 1)
    return -1;

  if (str[1] == '-')
  {
    if (str.size() == 2)
      return -1;
    str.erase(0, 2);
  }
  else if (str.size() == 2)
    str.erase(0, 1);
  else
    return -1;

  for (unsigned i = 0; i < PRON_NUM_OPTIONS; i++)
  {
    if (str == OPT_LIST[i].shortName || str == OPT_LIST[i].longName)
    {
      if (OPT_LIST[i].numArgs == 1)
      {
        if (nextToken+1 >= argc)
          return -1;

        if (argv[nextToken+1][0] != '"')
        {
          optarg = argv[nextToken+1];
          nextToken += 2;
          return str[0];
        }

        // Poor man's quote removal.
        string cumul(argv[nextToken+1] + 1);
        while (nextToken+1 < argc && cumul.back() != '"')
        {
          nextToken++;
          cumul += " " + string(argv[nextToken+1]);
        }

        if (nextToken+1 >= argc)
          return -1;

        cumul.pop_back();
        optarg = cumul;

        nextToken += 2;
      }
      else
        nextToken++;

      return str[0];
    }
  }

  return -1;
}


static void setDefaults(Options& options)
{
  options.wordInput = {false, ""};
  options.phraseInput = {false, ""};
  options.fileInput = {false, ""};
  options.dirInput = {false, ""};

  options.vowelsFlag = false;
  options.exactFlag = false;

  options.formatSetFlag = true;
  options.format = PRON_FORMAT_TXT;

  options.collisionsFlag = false;
}


static void printFileOption(
  const FileOption& fopt,
  const string& text)
{
  cout << setw(12) << text;
  if (fopt.setFlag)
    cout << setw(12) << fopt.name << "\n";
  else
    cout << setw(12) << "not set" << "\n";
}


static void printBinaryOption(
  const bool flag,
  const string& text)
{
  if (flag)
    cout << setw(12) << text << "set\n";
  else
    cout << setw(12) << text << "not set" << "\n";
}


void printOptions(const Options& options)
{
  cout << left;
  printFileOption(options.wordInput, "inword");
  printFileOption(options.phraseInput, "inphrase");
  printFileOption(options.fileInput, "infile");
  printFileOption(options.dirInput, "indir");

  printBinaryOption(options.vowelsFlag, "vowels");
  printBinaryOption(options.exactFlag, "exact");


  if (options.formatSetFlag)
  {
    cout << setw(12) << "format" << 
        setw(12) << FORMAT_NAMES[options.format] << "\n";
  }
  else
    cout << setw(12) << "not set\n";

  printBinaryOption(options.collisionsFlag, "collisions");

  cout << "\n\n";
}


static void checkArgs(const Options& options)
{
  int c = 0;
  if (options.wordInput.setFlag) c++;
  if (options.phraseInput.setFlag) c++;
  if (options.fileInput.setFlag) c++;
  if (options.dirInput.setFlag) c++;

  if (c != 1)
  {
    cout << "Need exactly one of -w, -p, -i, -I." << 
      endl;
    exit(0);
  }
}


void readArgs(
  int argc,
  char * argv[],
  Options& options)
{
  for (unsigned i = 0; i < PRON_NUM_OPTIONS; i++)
  {
    shortOptsAll += OPT_LIST[i].shortName;
    if (OPT_LIST[i].numArgs)
      shortOptsWithArg += OPT_LIST[i].shortName;
  }

  if (argc == 1)
  {
    usage(argv[0]);
    exit(0);
  }

  setDefaults(options);

  int c;
  bool errFlag = false, matchFlag;
  string stmp;

  while ((c = getNextArgToken(argc, argv)) > 0)
  {
    switch(c)
    {
      case 'w':
        options.wordInput = {true, string(optarg)};
        break;

      case 'i':
        options.fileInput = {true, optarg};
        break;

      case 'I':
        options.dirInput = {true, optarg};
        break;

      case 'v':
        options.vowelsFlag = true;
        break;

      case 'e':
        options.exactFlag = true;
        break;

      case 'f':
        matchFlag = false;
        for (unsigned i = 0; i < PRON_FORMAT_SIZE; i++)
        {
          if (FORMAT_NAMES[i] != optarg)
            continue;

          matchFlag = true;
          options.formatSetFlag = true;
          options.format = static_cast<Format>(i);
          break;
        }

        if (! matchFlag)
        {
          cout << "Could not parse format\n";
          nextToken -= 2;
          errFlag = true;
        }
        break;

      case 'c':
        options.collisionsFlag = true;
        break;

      default:
        cout << "Unknown option\n";
        errFlag = true;
        break;
    }
    if (errFlag)
      break;
  }

  if (errFlag || c == -1)
  {
    cout << "Error while parsing option '" << argv[nextToken] << "'\n";
    cout << "Invoke the program without arguments for help" << endl;
    exit(0);
  }

  checkArgs(options);
}

