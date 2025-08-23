#ifndef _VK_GRAPHICSPIPELINE_SHADERSTAGECREATEINFO_H
#define _VK_GRAPHICSPIPELINE_SHADERSTAGECREATEINFO_H

void vk_setVkPipelineShaderStageCreateInfo(uint32_t device, char *vert, char *frag, VkShaderModule *vkshadermodule_vert_p, VkShaderModule *vkshadermodule_frag_p, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p);

#endif