#ifndef NALI_VK_GRAPHICSPIPELINES_H
#define NALI_VK_GRAPHICSPIPELINES_H

void vk_makeGraphicsPipeline(uint32_t device, VkPipelineCreateFlags vkpipelinecreateflags, VkRenderPass* vkrenderpass_ptr, VkPipelineLayout* vkpipelinelayout_ptr, VkPipeline* vkpipeline_ptr);

#endif