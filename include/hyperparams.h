// hyperparam.h

#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

enum LayerType
{
  CONVOLUTION, POOLING, FULL
};

struct LayerHParam
{
    const int inputWidth;
    const int inputHeight;
    const int inputDepth;
    const int stride;
    const int padding;
    const int startAddr;
    const int filterSize;
    LayerType layerType;

    LayerHParam(int inputWidth_p, int inputHeight_p, int inputDepth_p, int filterSize_p, int stride_p, int padding_p,
                LayerType layerType_p, int startAddr_p) :
            inputWidth(inputWidth_p),
            inputHeight(inputHeight_p),
            inputDepth(inputDepth_p),
            stride(stride_p),
            padding(padding_p),
            startAddr(startAddr_p),
            filterSize(filterSize_p),
            layerType(layerType_p)
    {}

    virtual ~LayerHParam() = default;
};

struct ConvLayerHParam : public LayerHParam
{
    const int nbOfFilter;

    ConvLayerHParam(int inputWidth_p, int inputHeight_p, int inputDepth_p, int nbOfFilter_p, int filterSize_p,
                    int stride_p, int padding_p, int startAddr_p) :
            LayerHParam(inputWidth_p, inputHeight_p, inputDepth_p, filterSize_p, stride_p, padding_p, CONVOLUTION, startAddr_p),
            nbOfFilter(nbOfFilter_p)
    {}
};

struct PoolLayerHParam : public LayerHParam
{
    const int nextDepthOffset;

    PoolLayerHParam(int inputWidth_p, int inputHeight_p, int inputDepth_p, int filterSize_p, int stride_p,
                    int padding_p, int startAddr_p) :
            LayerHParam(inputWidth_p, inputHeight_p, inputDepth_p, filterSize_p, stride_p, padding_p, POOLING, startAddr_p),
            nextDepthOffset((inputDepth_p > 0) ? (inputHeight_p * inputWidth_p) : 0)
    {}

    PoolLayerHParam(int inputWidth_p, int inputHeight_p, int inputDepth_p, int filterSize_p, int stride_p,
                    int padding_p, int nextDepthOffset_p, int startAddr_p) :
            LayerHParam(inputWidth_p, inputHeight_p, inputDepth_p, filterSize_p, stride_p, padding_p, POOLING, startAddr_p),
            nextDepthOffset(nextDepthOffset_p)
    {}
};

struct FullyConnectedHParam : public LayerHParam
{
    const int nbOfFilter;

    FullyConnectedHParam(int inputWidth_p, int inputHeight_p, int nbOfFilter_p, int filterSize_p, int startAddr_p) :
            LayerHParam(inputWidth_p, inputHeight_p, 1, filterSize_p, 1, 0, FULL, startAddr_p),
            nbOfFilter(nbOfFilter_p)
    {}
};

#endif
