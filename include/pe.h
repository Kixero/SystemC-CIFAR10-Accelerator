// pe.h

#ifndef PE_H
#define PE_H

#include <systemc.h>

template <typename T>
SC_MODULE(pe)
{
    sc_in<T> weight;
    sc_in<T> data_in;
    sc_in<T> part_res;

    sc_out<T> data_out;
    sc_out<T> output;

    sc_in<bool> clk;

    T delayReg;

    void step()
    {
        data_out = delayReg;
        delayReg = data_in;
        output = (weight * data_in) + part_res;
    }
    SC_CTOR(pe)
    {
        SC_METHOD(step);
        sensitive << clk.pos();
    }
};

#endif