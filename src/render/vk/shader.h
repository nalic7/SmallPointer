#ifndef _VK_SD_H
#define _VK_SD_H
	#define _VK_SD_MD_MAKE(device, code, size, vkshadermodule_p) \
		NALI_D_INFO \
		( \
			"vkCreateShaderModule %d", \
			vkCreateShaderModule \
			( \
				_vkq_dv_p[device], \
				&(VkShaderModuleCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, \
					.pCode = code, \
					.codeSize = size, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkshadermodule_p \
			) \
		)
#endif
