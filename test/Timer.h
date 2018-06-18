/*
   Pron, a wrapper for a ported and somewhat modified Metapron3.

   All Metapron3 copyright (C) 2010 Lawrence Philips.
   Copyright (C) 2018 by Soren Hein for the changes.

   See LICENSE and README.
*/

#ifndef PRON_TIMER_H
#define PRON_TIMER_H

#pragma warning(push)
#pragma warning(disable: 4365 4571 4625 4626 4774 5026 5027)
#include <chrono>
#pragma warning(pop)

using namespace std;

class Timers;


class Timer
{
  private:

    unsigned no;
    double sum;
    std::chrono::time_point<std::chrono::high_resolution_clock> begin;


  public:

    Timer();

    ~Timer();

    void reset();

    void start();

    void stop();

    void operator += (const Timer& timer2);

    string str(const int prec = 1) const;
};

#endif

