#include <vulkan/vulkan.h>
#include <vector>
#include <string.h>
#include <iostream>
#include "OutputBuffer.hpp"
#include "InputBuffer.hpp"

const int WORKGROUP_SIZE = 32;

// Used for validating return values of Vulkan API calls.
#define VK_CHECK_RESULT(f) 																				\
{																										\
    VkResult res = (f);																					\
    if (res != VK_SUCCESS)																				\
    {																									\
        printf("Fatal : VkResult is %d in %s at line %d\n", res,  __FILE__, __LINE__); \
    }																									\
}

class MatrixMultiplier {
public:

    MatrixMultiplier(int rows, int cols);
    ~MatrixMultiplier();

    void UploadData(float* data);
    void ReadData(float* data);
    void Run();


    
private:

    void CreateInstance();
    void FindPhysicalDevice();
    uint32_t GetComputeQueueFamilyIndex();
    void CreateDevice();
    void CreateDescriptorSetLayout();
    void CreateDescriptorSet();
    uint32_t* ReadFile(uint32_t& length, const char* filename);
    void CreateComputePipeline();
    void CreateCommandBuffer();
    void CreateSyncObjects();
    
    uint32_t currentFrame = 0;
    int m_Rows = 0;
    int m_Cols = 0;
    VkInstance instance;
    VkDebugReportCallbackEXT debugReportCallback;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    VkShaderModule computeShaderModule;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    std::vector<VkFence> inFlightFences;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkDescriptorSetLayout descriptorSetLayout;
    VkQueue queue;
    uint32_t queueFamilyIndex;
    OutputBuffer outputBuffer;
    InputBuffer inputBuffer;

};