void vk_makeSampler(uint32_t device, VkSamplerCreateFlags vksamplercreateflags, VkSampler* vksampler_p)
{
	VkSamplerCreateInfo vksamplercreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.anisotropyEnable = VK_FALSE,
		.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		.unnormalizedCoordinates = VK_FALSE,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_ALWAYS,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,

		.flags = vksamplercreateflags,
		.mipLodBias = 0,
		.maxAnisotropy = 0,
		.minLod = 0,
		.maxLod = 0,

		.pNext = VK_NULL_HANDLE
	};

	vkCreateSampler(m_vkdevice_p[device], &vksamplercreateinfo, VK_NULL_HANDLE, vksampler_p);
}