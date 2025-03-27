void vk_makeDescriptorSetLayout(uint32_t device, VkDescriptorSetLayoutBinding *vkdescriptorsetlayoutbinding_p, uint32_t vkdescriptorsetlayoutbinding_size, VkDescriptorSetLayout *vkdescriptorsetlayout_p)
{
	VkDescriptorSetLayoutCreateInfo vkdescriptorsetlayoutcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.bindingCount = vkdescriptorsetlayoutbinding_size,
		.pBindings = vkdescriptorsetlayoutbinding_p,

		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateDescriptorSetLayout(m_vkdevice_p[device], &vkdescriptorsetlayoutcreateinfo, VK_NULL_HANDLE, vkdescriptorsetlayout_p);
}