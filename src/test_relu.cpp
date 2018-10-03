// test_relu.cpp

#include <systemc.h>
#include "types.h"
#include "cycle.h"
#include "relu.h"

void test_relu()
{
  sc_signal<DataType> data_in;
  sc_signal<DataType> data_out;

  sc_signal<bool> clk;

  sc_trace_file *my_trace;
  my_trace = sc_create_vcd_trace_file("relu_trace");
  my_trace->set_time_unit(1, SC_NS);

  sc_trace(my_trace, data_in, "data_in");
  sc_trace(my_trace, data_out, "data_out");
  sc_trace(my_trace, clk, "clk");

  DataType data[5] = {-2, 5, 3, -3, 2};

  relu relu("relu");
  relu.data_in(data_in);
  relu.data_out(data_out);
  relu.clk(clk);

  for (int i = 0; i < 5; i++)
  {
    data_in = data[i];
    next_cycle(clk);
  }
}
