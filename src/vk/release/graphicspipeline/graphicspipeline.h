#ifndef NALI_VK_GRAPHICSPIPELINES_H
#define NALI_VK_GRAPHICSPIPELINES_H

void vk_makeGraphicsPipeline(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass vkrenderpass, VkPipelineLayout vkpipelinelayout, VkPipeline *vkpipeline_p);

#endif