void vk_makeDescriptorSetLayout(uint32_t device, VkDescriptorSetLayoutCreateFlags vkdescriptorsetlayoutcreateflags, VkDescriptorSetLayout *vkdescriptorsetlayout_p)
{
	VkDescriptorSetLayoutBinding vkdescriptorsetlayoutbinding =
	{
		.binding = 0,
		.descriptorCount = 1,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,//VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
		.pImmutableSamplers = VK_NULL_HANDLE,
		.stageFlags = VK_SHADER_STAGE_VERTEX_BIT//VK_SHADER_STAGE_FRAGMENT_BIT
	};

	VkDescriptorSetLayoutCreateInfo vkdescriptorsetlayoutcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.bindingCount = 1,
		.pBindings = &vkdescriptorsetlayoutbinding,

		.flags = vkdescriptorsetlayoutcreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateDescriptorSetLayout(m_vkdevice_p[device], &vkdescriptorsetlayoutcreateinfo, VK_NULL_HANDLE, vkdescriptorsetlayout_p);
}