// memory.h

#ifndef MEMORY_H
#define MEMORY_H

#include <systemc.h>
#include <vector>

using namespace std;

template <typename T, int size>
SC_MODULE(memory)
{
  sc_in<T> data_in;
  sc_out<T> data_out;

  sc_in<bool> w_e;    //Write Enable
  sc_in<int> addr_r;
  sc_in<int> addr_w;

  sc_in<bool> clk;

  vector<T> memorySpace;

  void step()
  {
    if (w_e && addr_w < size)
    {
      memorySpace[addr_w] = data_in;
    }
    data_out = memorySpace[addr_r];
  }

public:
  void loadMemory(vector<T> data)
  {
    for (int i = 0; i < size; i++)
    {
      memorySpace[i] = data[i];
    }
  }

  vector<T> getMemory()
  {
    return memorySpace;
  }

  SC_CTOR(memory):
    memorySpace(size, T(0))
  {
    SC_METHOD(step);
    sensitive << clk.pos();
  }
};

#endif
