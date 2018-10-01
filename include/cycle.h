// cycle.h

#ifndef CYCLE_H
#define CYCLE_H

#include <systemc.h>

extern void next_cycle(sc_signal<bool> &clk, int half_period = 5);

#endif
