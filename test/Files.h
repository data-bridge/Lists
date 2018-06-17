/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_FILES_H
#define PRON_FILES_H

#include "const.h"

using namespace std;


struct FileEntry
{
  string fullName;
  string base;
  Format format;
};


class Files
{
  private:

    unsigned nextNo;

    vector<string> dirList; // Sloppy to keep this

    bool fillEntry(
      const string& text,
      FileEntry& entry) const;

    void list2map(
      const vector<FileEntry>& fileList,
      map<string, vector<FileEntry>>& refMap);

    void buildFileList(
      const string& dirName,
      vector<FileEntry>& fileList,
      const Format formatOnly = BRIDGE_FORMAT_SIZE);

    Format guessLINFormat(const string& base) const;

    void extendTaskList(
      const FileEntry& in,
      const vector<FileEntry>& out,
      const bool keepFlag,
      const map<string, vector<FileEntry>>& refMap);


  public:

    Files();

    ~Files();

    void reset();

    void rewind();

    void set(const Options& options);

    bool next(FileTask& ftask);

    void print() const;
};

#endif

