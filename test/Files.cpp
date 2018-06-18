/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#include <iostream>
#include <fstream>
#include <regex>

#if defined(__CYGWIN__)
  #include "dirent.h"
#elif defined(_WIN32)
  #include "dirent.h"
  #include <windows.h>
  #include "Shlwapi.h"
#else
  #include <dirent.h>
#endif

#include "Files.h"
#include "parse.h"


Files::Files()
{
  Files::reset();
}


Files::~Files()
{
}


void Files::reset()
{
  nextNo = 0;
  inputList.clear();
}


void Files::rewind()
{
  nextNo = 0;
}


bool Files::fillEntry(
  const string& text,
  FileEntry& entry) const
{
  regex re("([^./]+)\\.(\\w+)$");
  smatch match;
  if (regex_search(text, match, re) && match.size() >= 2)
  {
    entry.fullName = text;
    entry.base = match.str(1);
    entry.format = ext2format(match.str(2));
    return true;
  }
  else
    return false;
}


void Files::buildFileList(
  const string& dirName,
  vector<FileEntry>& fileList,
  const Format format)
{
  DIR *dir;
  struct dirent *ent;
  FileEntry entry;

  if ((dir = opendir(dirName.c_str())) == nullptr) 
    return;
  dirList.push_back(dirName);

  while ((ent = readdir(dir)) != nullptr) 
  {
    string s = dirName + "/" + string(ent->d_name);
    switch (ent->d_type)
    {
      case DT_REG:
        if (Files::fillEntry(s, entry))
        {
          if (entry.format == format)
            fileList.push_back(entry);
        }
        break;

      case DT_DIR:
        if (strcmp(ent->d_name, ".") != 0 &&
            strcmp(ent->d_name, "..") != 0)
        {
          Files::buildFileList(s, fileList, format);
        }

      default:
        break;
    }
  }
  closedir(dir);
}


void Files::set(const Options& options)
{
  // Set inputList
  if (options.fileInput.setFlag)
  {
    FileEntry e;
    if (Files::fillEntry(options.fileInput.name, e))
      inputList.push_back(e);
  }
  else
  {
    dirList.clear();
    Files::buildFileList(options.dirInput.name, inputList, 
      PRON_FORMAT_TXT);
  }
}


bool Files::next(FileEntry& ftask) 
{
  if (nextNo >= inputList.size())
    return false;

  ftask = inputList[nextNo++];
  return true;
}


void Files::print() const
{
  for (auto &i: inputList)
  {
    cout << "fullname  " << i.fullName << endl;
    cout << "base      " << i.base << endl;
    cout << "format    " << FORMAT_NAMES[i.format] << endl << endl;
  }
}

