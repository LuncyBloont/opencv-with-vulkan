#ifndef CVVK_VK_GPU_MEME_H
#define CVVK_VK_GPU_MEME_H

#include "helper.h"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <set>
#include <stdexcept>
#include <stdint.h>
#include <vulkan/vulkan.h>

namespace mltsg 
{

#define MLTSG_DEFAULT_T_MEM_SIZE (32 * 1024 * 1024 * 8 * 2)
#define MLTSG_DEFAULT_V_MEM_SIZE (10000 * 4 * 4 * 16 * 8 * 32)
#define MLTSG_DEFAULT_U_MEM_SIZE (16 * 128 * 256)
#define MLTSG_DEFAULT_TRANS_SIZE (8 * 4096 * 4096 * 4)
#define MLTSG_DEFAULT_I_MEM_SIZE (16 * 8 * 100000)

class GPUMem
{
private:
    struct MemSeg
    {
        VkDeviceSize start = 0;
        VkDeviceSize size = 0;

        explicit MemSeg(VkDeviceSize start = 0, VkDeviceSize size = 0);

        bool operator<(const MemSeg& other) const;
    };

    VkDeviceMemory memory;
    std::set<MemSeg> used;
    VkDeviceSize size;
    VkMemoryRequirements memoryType;
    VkMemoryPropertyFlags properties;

public: 
    explicit GPUMem(VkDeviceSize size, const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties);
    virtual ~GPUMem();

    GPUMem(const GPUMem&) = delete;
    GPUMem(const GPUMem&&) = delete;
    GPUMem& operator=(const GPUMem&&) = delete;
    GPUMem& operator=(const GPUMem&) = delete;

    bool isCompatible(const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties) const;
    bool check() const;
    VkDeviceSize alloc(VkDeviceSize size, VkDeviceSize alignment);
    bool free(VkDeviceSize ptr);
    const VkDeviceMemory& vulkanMemory() const;
    
};

struct GPUPtr
{
    GPUMem* area;
    VkDeviceSize ptr;
};

template <uint32_t Count>
struct GPUMemsArray
{
    std::array<GPUMem*, Count> arr = {};
    const uint32_t count = Count;

    const char* name;

    explicit GPUMemsArray(const char* name) : name(name)
    {}

    GPUPtr memoryAllocate(const VkMemoryRequirements& requirements, VkDeviceSize size, VkDeviceSize iniSize, VkMemoryPropertyFlags properties)
    {
        for (uint32_t i = 0; i < count; ++i) {
            if (arr[i] == nullptr)
            {
                MLTSG_LogDB("%s GPUMemArray create area %d\n", name, i);
                arr[i] = new GPUMem(iniSize, requirements, properties);
            }
            if (arr[i]->isCompatible(requirements, properties))
            {
                GPUPtr ptr { arr[i], arr[i]->alloc(size, requirements.alignment) };
                return ptr;
            }
        }

        mltsg::LogErr("CPU Memory Array allocate error: no available GPUMem.\n");
        throw std::runtime_error("GPUMemArray alloc");
    }

    void memoryDisable()
    {
        for (uint32_t i = 0; i < count; ++i) {
            if (arr[i] != nullptr)
            {
                delete arr[i];
                arr[i] = nullptr;
            }
        }
    }
};

uint32_t findMemoryIndex(uint32_t typeFilter, VkMemoryPropertyFlags properties);

}

#endif