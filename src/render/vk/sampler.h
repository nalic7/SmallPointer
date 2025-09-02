#ifndef SMPT_RD_VK_SP_H
	#define SMPT_RD_VK_SP_H

	//.i mipmap 0
	#define SMPT_RD_VK_SP_MAKE(device, mipmap, line, vksampler_p) \
		VkSamplerCreateInfo vksamplercreateinfo = \
		{ \
			.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO, \
			.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT, \
			.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT, \
			.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT, \
			.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK, \
			.unnormalizedCoordinates = VK_FALSE, \
			.compareEnable = VK_FALSE, \
			.compareOp = VK_COMPARE_OP_ALWAYS, \
			.anisotropyEnable = SMPT_RD_VK_MAX_SAMPLER_ANISOTROPY == 0 ? VK_FALSE : VK_TRUE, \
			.maxAnisotropy = SMPT_RD_VK_MAX_SAMPLER_ANISOTROPY, \
			.mipLodBias = 0, \
			.minLod = 0, \
			.maxLod = mipmap, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		}; \
		if (line) \
		{ \
			vksamplercreateinfo.magFilter = VK_FILTER_LINEAR; \
			vksamplercreateinfo.minFilter = VK_FILTER_LINEAR; \
			vksamplercreateinfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR; \
		} \
		else \
		{ \
			vksamplercreateinfo.magFilter = VK_FILTER_NEAREST; \
			vksamplercreateinfo.minFilter = VK_FILTER_NEAREST; \
			vksamplercreateinfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST; \
		} \
		SMPT_DB_R2L("vkCreateSampler %d", vkCreateSampler(smpt_rd_vkq_dv_p[device], &vksamplercreateinfo, VK_NULL_HANDLE, vksampler_p))
#endif
