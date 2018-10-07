// mpectrlr.h

#ifndef MPECTRLR_H
#define MPECTRLR_H

#include <systemc.h>
#include <vector>
#include <iostream>
#include "hyperparams.h"
#include "ctrlrconsts.h"

using namespace std;

SC_MODULE(mpectrlr)
{
  sc_in<bool> start;          /// Start signal
  sc_in<bool> clk;            /// Clock signal

  sc_out<int> addr_r;         /// Address to load
  sc_out<int> addr_w;         /// Address counter where to write MPE output
  sc_out<bool> w_e;           /// Write enable signal for the memory
  sc_out<bool> clear;         /// Clear maximum signal for the MPE

  enum State
  {
      IDLE, NORMAL
  };                          /// Enumeration of possible states
  State _state;               /// State of the controller

  vector<CtrlrConsts> _ctrlrConsts;   /// Constants used by the controller
  CtrlrConsts _currentConsts;         /// Constants currently in use

  int _stepCount;             /// Step Counter
  int _phaseCount;            /// Phase Counter

  int _readAddr;              /// Address to load
  int _writeAddr;             /// Address counter where to write MPE output
  bool _writeEnable;          /// Write enable signal for the memory
  bool _clearMax;             /// Clear maximum signal for the MPE

  int _xPosInside;            /// X position of the value inside the filter
  int _yPosInside;            /// Y position of the value inside the filter
  int _xPosFilter;            /// X position of the filter inside the input image
  int _yPosFilter;            /// Y position of the filter inside the input image
  int _zPos;                  /// Z position inside the input image

  void step();
  void normalState();
  void idleState();

  SC_HAS_PROCESS(mpectrlr);

  mpectrlr(sc_module_name name, vector<CtrlrConsts> ctrlrConsts):
    sc_module(name),
    _state(IDLE),
    _ctrlrConsts(move(ctrlrConsts)),
    _currentConsts(_ctrlrConsts[0]),
    _stepCount(0),
    _phaseCount(0),

    _readAddr(0),
    _writeAddr(0),
    _writeEnable(false),
    _clearMax(false),

    _xPosInside(0),
    _yPosInside(0),
    _xPosFilter(0),
    _yPosFilter(0),
    _zPos(0)
  {
    SC_METHOD(step);
    sensitive << clk.pos();
  }
};

#endif
