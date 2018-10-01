// test_memory.cpp

#include <systemc.h>
#include "cycle.h"
#include "types.h"
#include "memory.h"

void test_memory()
{
  sc_signal<DataType> data_in;
  sc_signal<DataType> data_out;

  sc_signal<int> addr_r;
  sc_signal<int> addr_w;

  sc_signal<bool> w_e;

  sc_signal<bool> clk;

  DataType data[12] = {2, 12, 3, 9, 2, 7, 3, 9, 7, 0, 3, 8};

  sc_trace_file *trace_file;
  trace_file = sc_create_vcd_trace_file("memory_trace");
  trace_file->set_time_unit(1, SC_NS);

  sc_trace(trace_file, data_in, "data_in");
  sc_trace(trace_file, data_out, "data_out");
  sc_trace(trace_file, w_e, "w_e");
  sc_trace(trace_file, addr_r, "addr_r");
  sc_trace(trace_file, addr_w, "addr_w");
  sc_trace(trace_file, clk, "clk");

  memory<DataType, 12> memory("/memory");
  memory.data_in(data_in);
  memory.data_out(data_out);
  memory.addr_r(addr_r);
  memory.addr_w(addr_w);
  memory.clk(clk);
  memory.w_e(w_e);

  for (int i = 0; i < 12; i++)
  {
    addr_r = i;
    addr_w = i;
    w_e = true;
    data_in = data[i];
    next_cycle(clk);
  }
  w_e = false;
  addr_r = 2;
  next_cycle(clk);
  addr_r = 8;
  next_cycle(clk);
  addr_w = 5;
  data_in = 6;
  w_e = true;
  addr_r = 5;
  next_cycle(clk);
  w_e = false;
  next_cycle(clk);
  next_cycle(clk);

  sc_close_vcd_trace_file(trace_file);
}
