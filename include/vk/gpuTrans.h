#pragma once

#include "gpuMat.h"
#include "opencv2/core/mat.hpp"

void initializeMemoryTransfer();

void copyMat2GPUMat(const cv::Mat& mat, GPUMat& gmat);
void copyGPUMat2Mat(GPUMat& gmat, cv::Mat& mat);