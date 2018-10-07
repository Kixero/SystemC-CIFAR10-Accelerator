// memory.h

#ifndef MEMORY_H
#define MEMORY_H

#include <systemc.h>

template <typename T, int size>
SC_MODULE(memory)
{
  sc_in<T> data_in;
  sc_out<T> data_out;

  sc_in<bool> w_e;    //Write Enable
  sc_in<int> addr_r;
  sc_in<int> addr_w;

  sc_in<bool> clk;

  T memorySpace[size];

  void step()
  {
    if (w_e)
    {
      memorySpace[addr_w] = data_in;
    }
    data_out = memorySpace[addr_r];
  }

  SC_CTOR(memory)
  {
    SC_METHOD(step);
    sensitive << clk.pos();
  }
};

#endif
