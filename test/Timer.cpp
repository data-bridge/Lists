/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#pragma warning(push)
#pragma warning(disable: 4365 4571 4625 4626 4774 5026 5027)
#include <iostream>
#include <iomanip>
#include <sstream>
#pragma warning(pop)

#include "Timer.h"


Timer::Timer()
{
  Timer::reset();
}


Timer::~Timer()
{
}


void Timer::reset()
{
  no = 0;
  sum = 0.;
}


void Timer::start()
{
  begin = std::chrono::high_resolution_clock::now();
}


void Timer::stop()
{
  auto end = std::chrono::high_resolution_clock::now();
  auto delta = std::chrono::duration_cast<std::chrono::microseconds>
    (end - begin);

  no++;
  sum += delta.count();
}


void Timer::operator += (const Timer& timer2)
{
  no += timer2.no;
  sum += timer2.sum;
}


string Timer::str(const int prec) const 
{
  if (no == 0)
    return "";

  stringstream ss;
  ss << fixed << setprecision(prec) << 
    sum / 1000000. << " seconds";
  if (no > 1)
    ss << " sum, " << sum / (1000. * no) << " ms average";
  return ss.str();
}

