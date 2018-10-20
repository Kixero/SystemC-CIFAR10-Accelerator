// test_pe.cpp

#include <systemc.h>
#include "pe.h"
#include "cycle.h"
#include "types.h"

void test_pe()
{
    sc_signal<DataType> data_in;
    sc_signal<DataType> part_res;
    sc_signal<DataType> weight;

    sc_signal<DataType> output;
    sc_signal<DataType> data_out;

    sc_signal<bool> clk;

    sc_trace_file *trace_file;
    trace_file = sc_create_vcd_trace_file("pe_trace");
    trace_file->set_time_unit(1, SC_NS);

    sc_trace(trace_file, data_in, "data_in");
    sc_trace(trace_file, part_res, "part_res");
    sc_trace(trace_file, weight, "weight");
    sc_trace(trace_file, output, "output");
    sc_trace(trace_file, data_out, "data_out");
    sc_trace(trace_file, clk, "clk");

    pe<DataType> pe("pe");
    pe.data_in(data_in);
    pe.part_res(part_res);
    pe.weight(weight);
    pe.output(output);
    pe.data_out(data_out);
    pe.clk(clk);

    DataType weights[4] = {3, 4, 7, 1};
    DataType data_inputs[4] = {2, 1, 3, 8};
    DataType inputs[4] = {7, 6, 3, 1};

    for (int i = 0; i < 4; i++)
    {
        data_in = data_inputs[i];
        part_res = inputs[i];
        weight = weights[i];
        next_cycle(clk);
    }

    sc_close_vcd_trace_file(trace_file);
}