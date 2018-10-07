// test_mpectrlr.cpp

#include <systemc.h>
#include <vector>
#include "cycle.h"
#include "hyperparams.h"
#include "ctrlrconsts.h"
#include "mpectrlr.h"

using namespace std;

void test_mpectrlr()
{
  sc_signal<bool> start;
  sc_signal<bool> clk;

  sc_signal<int> addr_r;
  sc_signal<int> addr_w;
  sc_signal<bool> clear;
  sc_signal<bool> w_e;

  sc_trace_file *my_trace;
  my_trace = sc_create_vcd_trace_file("mpectrlr_trace");
  my_trace->set_time_unit(1, SC_NS);

  sc_trace(my_trace, start, "start");
  sc_trace(my_trace, clk, "clk");
  sc_trace(my_trace, addr_r, "addr_r");
  sc_trace(my_trace, addr_w, "addr_w");
  sc_trace(my_trace, clear, "clear");
  sc_trace(my_trace, w_e, "w_e");

  auto HParam = PoolLayerHParam(24, 24, 3, 3, 2, 1, 1);

  auto poolConsts = CtrlrConsts(&HParam);

  vector<CtrlrConsts> consts{poolConsts};

  mpectrlr mpectrlr("mpectrlr", consts);

  mpectrlr.start(start);
  mpectrlr.clk(clk);
  mpectrlr.addr_r(addr_r);
  mpectrlr.addr_w(addr_w);
  mpectrlr.clear(clear);
  mpectrlr.w_e(w_e);

  start = false;
  next_cycle(clk);
  start = true;
  next_cycle(clk);

  for (int i = 0; i < poolConsts.MAX_STEPS; i++)
  {
    next_cycle(clk);
  }
}
