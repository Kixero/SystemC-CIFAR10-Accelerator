// mpectrlr.cpp

#include "mpectrlr.h"

void mpectrlr::idleState()
{
  _writeEnable = false;
  if (start.read() && _phaseCount < (int)_ctrlrConsts.size())
  {
      _state = NORMAL;
      _currentConsts = _ctrlrConsts[_phaseCount];
      _stepCount = 0;
      _xPosFilter = 0;
      _yPosFilter = 0;
      _xPosInside = 0;
      _yPosInside = 0;
      _zPos = 0;

      _writeAddr = _currentConsts.START_ADDR - 1;
  }
}

void mpectrlr::normalState()
{
  if (start.read())
  {
      /// End of phase
      if (_stepCount > _currentConsts.MAX_STEPS)
      {
          _state = IDLE;
          _phaseCount++;
          _writeEnable = false;
          _readAddr = 0;
      }
      else
      {
          /// Right padding
          if(_xPosFilter + _xPosInside >= _currentConsts.INPUT_WIDTH)
          {
              _readAddr = 0;
          }
          /// Bottom padding
          else if (_yPosFilter + _yPosInside >= _currentConsts.INPUT_SIZE)
          {
              _readAddr = 0;
          }
          /// Waiting for last save
          else if (_zPos > _currentConsts.MAX_Z_POS)
          {
              _readAddr = 0;
          }
          /// Computing read adress
          else
          {
              _readAddr = _currentConsts.START_ADDR
                        + _yPosFilter
                        + _xPosFilter
                        + _yPosInside
                        + _xPosInside
                        + _zPos;
          }

          _clearMax = _xPosInside + _yPosInside == _currentConsts.SAVE_TIME;

          _writeEnable = _clearMax && _stepCount >= _currentConsts.FILTER_STEPS;

          /// Moving filter
          _xPosInside++;
          if (_xPosInside == _currentConsts.FILTER_SIZE)
          {
              _xPosInside = 0;
              _yPosInside += _currentConsts.INPUT_WIDTH;

              if (_yPosInside == _currentConsts.MAX_FILTER_PER_ROW)
              {
                  _yPosInside = 0;
                  _xPosFilter += _currentConsts.STRIDE;

                  if (_xPosFilter == _currentConsts.MAX_X_POS)
                  {
                      _xPosFilter = 0;
                      _yPosFilter += _currentConsts.NEXT_FILTER_ROW;

                      if (_yPosFilter == _currentConsts.MAX_Y_POS)
                      {
                          _yPosFilter = 0;

                          if (_zPos < _currentConsts.MAX_Z_POS)
                          {
                              _zPos += _currentConsts.NEXT_DEPTH_OFFSET;
                          }
                      }
                  }
              }
          }

          /// Computing write adress
          if (_writeEnable)
          {
              _writeAddr++;

              if (_writeAddr - (_zPos - _currentConsts.NEXT_DEPTH_OFFSET) - _currentConsts.START_ADDR
                                                                  == _currentConsts.FILTERS_PER_DEPTH
               && _writeAddr > _currentConsts.FILTERS_PER_DEPTH)
              {
                  _writeAddr = _zPos + _currentConsts.START_ADDR;
              }
          }

          _stepCount++;
      }
  } else
  {
      _state = IDLE;
      _phaseCount++;
      _writeEnable = false;
      _readAddr = 0;
  }
}


void mpectrlr::step()
{
  switch (_state)
  {
      case IDLE:
          idleState();
          break;
      case NORMAL:
          normalState();
          break;
  }

  addr_r = _readAddr;
  addr_w = _writeAddr;
  w_e = _writeEnable;
  clear = _clearMax;
}
