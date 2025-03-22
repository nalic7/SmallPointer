void vk_makePipelineLayout(uint32_t device, VkPipelineLayoutCreateFlags vkpipelinelayoutcreateflags, VkDescriptorSetLayout *vkdescriptorsetlayout_p, uint32_t vkdescriptorsetlayout_size, VkPipelineLayout *vkpipelinelayout_p)
{
	VkPipelineLayoutCreateInfo vkpipelinelayoutcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,

		.setLayoutCount = vkdescriptorsetlayout_size,
		.pSetLayouts = vkdescriptorsetlayout_p,

		.pushConstantRangeCount = 0,
		.pPushConstantRanges = VK_NULL_HANDLE,

		.flags = vkpipelinelayoutcreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreatePipelineLayout(m_vkdevice_p[device], &vkpipelinelayoutcreateinfo, VK_NULL_HANDLE, vkpipelinelayout_p);
}