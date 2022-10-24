#include "vkHelper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <stdexcept>
#include <stdint.h>
#include <vcruntime.h>
#include <vcruntime_string.h>
#include <vector>

void readShader(VkShaderModule& shader, std::string fname)
{
    std::vector<char> codes;

    SHADER_INFO info{};

    std::ifstream file(fname, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "\033[31mFailed to read shader file (" << fname << ")\n\033[0m";
        throw std::runtime_error("read shader");
    }

    while (file.peek() != EOF)
    {
        char p;
        file.read(&p, 1);
        codes.push_back(p);
    }

    file.close();

    info.codeSize = codes.size();
    info.pCode = reinterpret_cast<uint32_t*>(codes.data());

    Log("Load shader %s (size: %llu)\n", CSTR(fname), info.codeSize);
    
    trydo(VK_SUCCESS) = vkCreateShaderModule(gVkDevice, &info, GVKALC, &shader);
}