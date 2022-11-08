#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "vkenv.h"

struct Context
{
    cv::Mat mtex0Data;
    mltsg::GPUMat* mtex0;

    Context()
    {
        mtex0Data = mltsg::imreadRGB(MLTSG_PATH("/images/Bricks.png"));
        mtex0 = new mltsg::GPUMat(&mtex0Data);
        mtex0->apply();

        
    }

    ~Context()
    {
        delete mtex0;
    }
};  

int main()
{
    mltsg::Log("Program start\n");

    mltsg::initializeVulkan();



    mltsg::cleanupVulkan();

    mltsg::Log("Program exit\n");
    return 0;
}