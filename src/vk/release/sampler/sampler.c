void vk_makeSampler(uint32_t device, uint32_t mipmap, uint8_t line, VkSampler *vksampler_p)
{
	VkSamplerCreateInfo vksamplercreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		.unnormalizedCoordinates = VK_FALSE,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_ALWAYS,

		.anisotropyEnable = NALI_VK_MAX_SAMPLER_ANISOTROPY == 0 ? VK_FALSE : VK_TRUE,
		.maxAnisotropy = NALI_VK_MAX_SAMPLER_ANISOTROPY,

		.mipLodBias = 0,
		.minLod = 0,
		.maxLod = mipmap,//0

		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	if (line)
	{
		vksamplercreateinfo.magFilter = VK_FILTER_LINEAR;
		vksamplercreateinfo.minFilter = VK_FILTER_LINEAR;
		vksamplercreateinfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	}
	else
	{
		vksamplercreateinfo.magFilter = VK_FILTER_NEAREST;
		vksamplercreateinfo.minFilter = VK_FILTER_NEAREST;
		vksamplercreateinfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
	}

	nali_info("vkCreateSampler %d", vkCreateSampler(m_vkdevice_p[device], &vksamplercreateinfo, VK_NULL_HANDLE, vksampler_p))
}