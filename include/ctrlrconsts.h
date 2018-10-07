// ctrlrconsts.h

#ifndef CTRLRCONSTS_H
#define CTRLRCONSTS_H

#include "hyperparams.h"

enum Multiplex
{
    CONV, MAXPOOL, ADD, MULTIPLEX_SIZE
};

/**
* @brief Constants for the Controllers
*/
struct CtrlrConsts
{
    int INPUT_WIDTH;
    int INPUT_HEIGHT;
    int INPUT_DEPTH;
    int INPUT_SIZE;
    int STRIDE;
    int PADDING;
    int MAX_STEPS;
    int TOP_PAD_STEPS;
    int DATA_IN_STEPS;
    int DATA_OUT_STEPS;
    int NEXT_ROW_STEPS;
    int NEXT_FILTER_ROW;
    int MAX_FILTER_PER_ROW;
    int MAX_X_POS;
    int MAX_Y_POS;
    int MAX_Z_POS;
    int NEXT_DEPTH_OFFSET;
    int FILTERS_PER_DEPTH;
    int FILTER_SIZE;
    int OUTPUT_SIZE;
    int FILTER_STEPS;
    int SAVE_TIME;
    int START_ADDR;

    Multiplex MULTIPLEX;

    explicit CtrlrConsts(LayerHParam *layerHParam);

    /**
    * @brief CtrlrConsts object default constructor
    */
    CtrlrConsts() :
            INPUT_WIDTH(0),
            INPUT_HEIGHT(0),
            INPUT_DEPTH(0),
            INPUT_SIZE(0),
            STRIDE(0),
            PADDING(0),
            MAX_STEPS(0),
            TOP_PAD_STEPS(0),
            DATA_IN_STEPS(0),
            DATA_OUT_STEPS(0),
            NEXT_ROW_STEPS(0),
            NEXT_FILTER_ROW(0),
            MAX_FILTER_PER_ROW(0),
            MAX_X_POS(0),
            MAX_Y_POS(0),
            MAX_Z_POS(0),
            NEXT_DEPTH_OFFSET(0),
            FILTERS_PER_DEPTH(0),
            FILTER_SIZE(0),
            OUTPUT_SIZE(0),
            FILTER_STEPS(0),
            SAVE_TIME(0),
            START_ADDR(0),
            MULTIPLEX(CONV)
    {}
};

#endif
