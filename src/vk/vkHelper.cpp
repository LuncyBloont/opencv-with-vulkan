#include "vkHelper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include <stdexcept>
#include <stdint.h>

uint32_t* codeBuffer = new uint32_t[MAX_SHADER_SIZE];

void readShader(VkShaderModule& shader, std::string fname)
{
    uint32_t size = 0;

    SHADER_INFO info{};

    std::ifstream file(fname);
    if (!file.is_open())
    {
        std::cerr << "\033[31mFailed to read shader file (" << fname << ")\n\033[0m";
        throw std::runtime_error("read shader");
    }

    uint32_t* p = codeBuffer;

    while (!file.eof() && p != codeBuffer + MAX_SHADER_SIZE)
    {
        file.read(reinterpret_cast<char*>(p), sizeof(uint32_t) / sizeof(char));
        size += sizeof(uint32_t);
        p++;
    }

    info.codeSize = size;
    info.pCode = codeBuffer;
    
    vkCreateShaderModule(gVkDevice, &info, GVKALC, &shader);
}