// mpe.h

#ifndef MPE_H
#define MPE_H

#include <systemc.h>

template <typename T>
SC_MODULE(mpe)
{
  sc_in<T> data_in;
  sc_out<T> data_out;

  sc_in<bool> clear;

  sc_in<bool> clk;

  T reg;

  void step()
  {
    if (clear)
    {
      reg = 0;
    }
    reg = reg < data_in ? data_in : reg;
    data_out = reg;
  }

  SC_CTOR(mpe)
  {
    SC_METHOD(step);
    sensitive << clk.pos();
  }
};

#endif
