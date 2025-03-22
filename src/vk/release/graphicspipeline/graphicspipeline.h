#ifndef NALI_VK_GRAPHICSPIPELINES_H
#define NALI_VK_GRAPHICSPIPELINES_H

void vk_makeGraphicsPipeline(uint32_t device, VkPipelineCreateFlags vkpipelinecreateflags, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass *vkrenderpass_p, VkPipelineLayout *vkpipelinelayout_p, VkPipeline *vkpipeline_p);

#endif