// test_mpe.cpp

#include <systemc.h>
#include "mpe.h"
#include "cycle.h"
#include "types.h"

void test_mpe()
{
  sc_signal<DataType> data_in;
  sc_signal<DataType> data_out;

  sc_signal<bool> clk;
  sc_signal<bool> clear;

  DataType data[12] = {2, 12, 3, 9, 2, 7, 3, 9, 7, 0, 3, 8};

  sc_trace_file *trace_file;
  trace_file = sc_create_vcd_trace_file("mpe_trace");
  trace_file->set_time_unit(1, SC_NS);

  sc_trace(trace_file, data_in, "data_in");
  sc_trace(trace_file, data_out, "data_out");
  sc_trace(trace_file, clear, "clear");
  sc_trace(trace_file, clk, "clk");

  mpe<DataType> mpe("mpe");
  mpe.data_in(data_in);
  mpe.data_out(data_out);
  mpe.clear(clear);
  mpe.clk(clk);

  for (int i = 0; i < 12; i++)
  {
    data_in = data[i];
    clear = (i % 4 == 0);
    next_cycle(clk);
  }

  sc_close_vcd_trace_file(trace_file);
}
