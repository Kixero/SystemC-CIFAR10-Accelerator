// test_pooling.cpp

#include <systemc.h>
#include <iostream>
#include "ctrlrconsts.h"
#include "cycle.h"
#include "types.h"
#include "memory.h"
#include "mpe.h"
#include "mpectrlr.h"

void test_pooling()
{
  sc_signal<DataType> data_r;
  sc_signal<DataType> data_w;

  sc_signal<int> addr_r;
  sc_signal<int> addr_w;

  sc_signal<bool> w_e;
  sc_signal<bool> clk;
  sc_signal<bool> start;
  sc_signal<bool> clear;

  sc_trace_file *trace_file;
  trace_file = sc_create_vcd_trace_file("pooling_trace");
  trace_file->set_time_unit(1, SC_NS);

  sc_trace(trace_file, data_r, "data_r");
  sc_trace(trace_file, data_w, "data_w");
  sc_trace(trace_file, w_e, "w_e");
  sc_trace(trace_file, addr_r, "addr_r");
  sc_trace(trace_file, addr_w, "addr_w");
  sc_trace(trace_file, clk, "clk");
  sc_trace(trace_file, start, "start");
  sc_trace(trace_file, clear, "clear");

  auto HParam = PoolLayerHParam(6, 6, 1, 2, 2, 0, 1);
  auto poolConsts = CtrlrConsts(&HParam);
  vector<CtrlrConsts> consts{poolConsts};

  memory<DataType, 37> memory("memory");
  mpe<DataType> mpe("mpe");
  mpectrlr mpectrlr("mpectrlr", consts);

  vector<DataType> data = {0,
                           2, 4, 1, 5, 9, 3,
                           1, 3, 8, 9, 0, 3,
                           2, 8, 4, 3, 9, 8,
                           5, 4, 5, 7, 3, 1,
                           8, 7, 9, 0, 3, 4,
                           3, 3, 2, 8, 2, 9};

  memory.loadMemory(data);

  memory.data_in(data_w);
  memory.data_out(data_r);
  memory.addr_r(addr_r);
  memory.addr_w(addr_w);
  memory.clk(clk);
  memory.w_e(w_e);

  mpe.data_in(data_r);
  mpe.data_out(data_w);
  mpe.clear(clear);
  mpe.clk(clk);

  mpectrlr.start(start);
  mpectrlr.clk(clk);
  mpectrlr.addr_r(addr_r);
  mpectrlr.addr_w(addr_w);
  mpectrlr.clear(clear);
  mpectrlr.w_e(w_e);

  start = false;
  next_cycle(clk);
  start = true;
  for (int i = 0; i < poolConsts.MAX_STEPS; i++)
  {
    next_cycle(clk);
  }

  sc_close_vcd_trace_file(trace_file);

  vector<DataType> output = memory.getMemory();
  for (int i = 1; i < 37; i++)
  {
    cout << "\t" << output[i];
    if (i % 6 == 0) {cout << endl;}
  }
}
