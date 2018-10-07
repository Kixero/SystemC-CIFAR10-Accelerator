// ctrlrconsts.cpp

#include "ctrlrconsts.h"

/**
* @brief CtrlrConsts object constructor
*
* @param cnnConfig Vector of LayHParams objects for each layer defining the config of the overall hyperparameters.
*        Object defined as a CNNConfig type
*/
CtrlrConsts::CtrlrConsts(LayerHParam *layerHParam) :
        CtrlrConsts()
{
    INPUT_WIDTH = layerHParam->inputWidth;

    INPUT_HEIGHT = layerHParam->inputHeight;

    INPUT_DEPTH = layerHParam->inputDepth;

    INPUT_SIZE = INPUT_WIDTH * INPUT_HEIGHT;

    PADDING = layerHParam->padding;

    STRIDE = layerHParam->stride;

    START_ADDR = layerHParam->startAddr;

    FILTER_SIZE = layerHParam->filterSize;

    switch (layerHParam->layerType)
    {
        case CONVOLUTION:
        {
            auto convLayerHParam = *dynamic_cast<ConvLayerHParam *>(layerHParam);

            MAX_STEPS = INPUT_HEIGHT * INPUT_WIDTH        /// Steps for all the image
                        + FILTER_SIZE * 2                 /// Steps between FIFO and output
                        + INPUT_WIDTH + PADDING * 2 - 1   /// Step to get the last input out
                        + PADDING * INPUT_WIDTH * 2       /// Steps for padding top and bottom
                        + PADDING * INPUT_HEIGHT * 2      /// Steps for padding sides
                        + PADDING * PADDING * 4           /// Steps for padding corners
                        + 1;                              /// RELU step

            TOP_PAD_STEPS = PADDING * INPUT_WIDTH         /// Top padding
                            + PADDING * PADDING * 2;      /// Corner padding

            DATA_IN_STEPS = INPUT_HEIGHT * INPUT_WIDTH    /// Inputs
                            + PADDING * INPUT_HEIGHT * 2  /// Side padding
                            + PADDING * INPUT_WIDTH       /// Top padding
                            + PADDING * PADDING * 2;      /// Corner padding

            DATA_OUT_STEPS = FILTER_SIZE * (INPUT_WIDTH + PADDING * 2)    /// FIFO fill-up
                             + FILTER_SIZE * 2 - 1                        /// PE steps
                             + FILTER_SIZE                                /// Adders steps
                             + 1;                                         /// RELU step
                             //+ 1;

            NEXT_ROW_STEPS = (INPUT_WIDTH           /// Scrap next row steps
                              + PADDING * 2         /// Scrap next row padding steps
                              + FILTER_SIZE - 1)    /// Scrap next row transition steps
                             * (STRIDE - 1)         /// ..for every stride > 1
                             - 1;                   /// -1 because it begin down counting next step

            OUTPUT_SIZE = (INPUT_WIDTH - FILTER_SIZE + 2 * PADDING) / STRIDE; // + 1;

            MULTIPLEX = CONV;
            break;
        }
        case POOLING:
        {
            auto poolLayerHParam = *dynamic_cast<PoolLayerHParam *> (layerHParam);

            NEXT_DEPTH_OFFSET = poolLayerHParam.nextDepthOffset;   /// Adress offset to next depth

            SAVE_TIME = 1;  /// Time to wait between output computation and save in memory
                            /// (Number of modules between MPE and Memory + 1)

            FILTER_STEPS = FILTER_SIZE * FILTER_SIZE;   /// Steps to complete one filter

            FILTERS_PER_DEPTH = (INPUT_HEIGHT / STRIDE) * (INPUT_HEIGHT / STRIDE);   /// Number of filter for each depth

            NEXT_FILTER_ROW = INPUT_WIDTH * STRIDE;   /// Adress to go for next next row for filter

            MAX_FILTER_PER_ROW = FILTER_SIZE * INPUT_WIDTH;   /// Number of filters per row

            MAX_X_POS = INPUT_WIDTH - INPUT_WIDTH % STRIDE;   /// Maximum X position for the filter

            MAX_Y_POS = (INPUT_HEIGHT - INPUT_HEIGHT % STRIDE) * INPUT_WIDTH;  /// Maximum Y position for the filter

            MAX_Z_POS = NEXT_DEPTH_OFFSET * (INPUT_DEPTH - 1);   /// Maximum Z position for the filter

            MAX_STEPS = (INPUT_WIDTH / STRIDE) * (INPUT_HEIGHT / STRIDE) * FILTER_STEPS * INPUT_DEPTH + SAVE_TIME + 3;  /// Steps for all the input

            MULTIPLEX = MAXPOOL;
            break;
        }
        case FULL:
        {
            auto fullLayerHParam = *dynamic_cast<ConvLayerHParam *> (layerHParam);

            MAX_STEPS = INPUT_HEIGHT * INPUT_WIDTH        /// Steps for all the image
                        + FILTER_SIZE * 2                 /// Steps between FIFO and output
                        + INPUT_WIDTH + PADDING * 2 - 1   /// Step to get the last input out
                        + PADDING * INPUT_WIDTH * 2       /// Steps for padding top and bottom
                        + PADDING * INPUT_HEIGHT * 2      /// Steps for padding sides
                        + PADDING * PADDING * 4           /// Steps for padding corners
                        + 1;                              /// RELU step

            TOP_PAD_STEPS = PADDING * INPUT_WIDTH         /// Top padding
                            + PADDING * PADDING * 2;      /// Corner padding

            DATA_IN_STEPS = INPUT_HEIGHT * INPUT_WIDTH    /// Inputs
                            + PADDING * INPUT_HEIGHT * 2  /// Side padding
                            + PADDING * INPUT_WIDTH       /// Top padding
                            + PADDING * PADDING * 2;      /// Corner padding

            DATA_OUT_STEPS = FILTER_SIZE * (INPUT_WIDTH + PADDING * 2)    /// FIFO fill-up
                             + FILTER_SIZE * 2 - 1                        /// PE steps
                             + FILTER_SIZE                                /// Adders steps
                             + 1;                                         /// RELU step
                           //+ 1;

            NEXT_ROW_STEPS = (INPUT_WIDTH           /// Scrap next row steps
                              + PADDING * 2         /// Scrap next row padding steps
                              + FILTER_SIZE - 1)    /// Scrap next row transition steps
                             * (STRIDE - 1)         /// ..for every stride > 1
                             - 1;                   /// -1 because it begin down counting next step

            OUTPUT_SIZE = fullLayerHParam.nbOfFilter;

            MULTIPLEX = CONV;
            break;
        }
    }
}
