// cycle.h

#include <systemc.h>

void next_cycle(sc_signal<bool> &clk, int half_period = 5)
{
  clk = true;
  sc_start(half_period, SC_NS);
  clk = false;
  sc_start(half_period, SC_NS);
}
