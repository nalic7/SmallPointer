void vkdslo_make(uint32_t device, VkDescriptorSetLayoutBinding *vkdescriptorsetlayoutbinding_p, uint32_t vkdescriptorsetlayoutbinding_size, VkDescriptorSetLayout *vkdescriptorsetlayout_p)
{
	nali_info
	(
		"vkCreateDescriptorSetLayout %d",
		vkCreateDescriptorSetLayout
		(
			vkqd_vkdevice_p[device],
			&(VkDescriptorSetLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
				.bindingCount = vkdescriptorsetlayoutbinding_size,
				.pBindings = vkdescriptorsetlayoutbinding_p,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkdescriptorsetlayout_p
		)
	)
}