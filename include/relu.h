// relu.h

#include <systemc.h>
#include "types.h"

SC_MODULE(relu)
{
  sc_in<DataType> data_in;
  sc_out<DataType> data_out;

  sc_in<bool> clk;

  void step()
  {
    data_out = data_in > 0 ? data_in : 0;
  }

  SC_CTOR(relu)
  {
    SC_METHOD(step);
    sensitive << clk;
  }
};
