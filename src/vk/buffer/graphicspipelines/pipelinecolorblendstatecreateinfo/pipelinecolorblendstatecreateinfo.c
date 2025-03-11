void vk_setPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* vkpipelinecolorblendattachmentstate_ptr, VkPipelineColorBlendStateCreateFlags vkpipelinecolorblendstatecreateflags, VkPipelineColorBlendStateCreateInfo* vkpipelinecolorblendstatecreateinfo_ptr)
{
	vkpipelinecolorblendstatecreateinfo_ptr->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	vkpipelinecolorblendstatecreateinfo_ptr->logicOpEnable = VK_FALSE;
	vkpipelinecolorblendstatecreateinfo_ptr->logicOp = VK_LOGIC_OP_COPY;
	vkpipelinecolorblendstatecreateinfo_ptr->attachmentCount = 1;
	vkpipelinecolorblendstatecreateinfo_ptr->pAttachments = vkpipelinecolorblendattachmentstate_ptr;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[0] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[1] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[2] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[3] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->flags = vkpipelinecolorblendstatecreateflags;
	vkpipelinecolorblendstatecreateinfo_ptr->pNext = VK_NULL_HANDLE;
}