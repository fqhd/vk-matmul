#include "OutputBuffer.hpp"
#include <iostream>
#include "VulkanUtils.hpp"
#include <cstring>

void OutputBuffer::Create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
{
    Size = size;
    m_Device = device;
    CreateBuffer(physicalDevice, device, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_StagingBuffer, m_StagingMemory);
    CreateBuffer(physicalDevice, device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, Buffer, Memory);
}

void OutputBuffer::ReadData(VkCommandPool pool, VkQueue queue, void* buffer)
{
    vkDeviceWaitIdle(m_Device);
    CopyBuffer(m_Device, pool, queue, Buffer, m_StagingBuffer, Size);
    void* mappedMemory = NULL;
    vkMapMemory(m_Device, m_StagingMemory, 0, Size, 0, &mappedMemory);
    memcpy(buffer, mappedMemory, Size);
    vkUnmapMemory(m_Device, m_StagingMemory);
}

void OutputBuffer::Destroy()
{
    vkFreeMemory(m_Device, m_StagingMemory, NULL);
    vkDestroyBuffer(m_Device, m_StagingBuffer, nullptr);
    vkFreeMemory(m_Device, Memory, NULL);
    vkDestroyBuffer(m_Device, Buffer, nullptr);
}