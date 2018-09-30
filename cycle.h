// cycle.h

#ifndef CYCLE_H
#define CYCLE_H

#include <systemc.h>

void next_cycle(sc_signal<bool> &clk, int half_period)
{
  clk = true;
  sc_start(half_period, SC_NS);
  clk = false;
  sc_start(half_period, SC_NS);
}

#endif
