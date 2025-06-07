void vksm_make(uint32_t device, uint32_t *uint32_t_p, size_t size, VkShaderModule *vkshadermodule_p)
{
	NALI_D_INFO
	(
		"vkCreateShaderModule %d",
		vkCreateShaderModule
		(
			vkqd_vkdevice_p[device],
			&(VkShaderModuleCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
				.pCode = uint32_t_p,
				.codeSize = size,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkshadermodule_p
		)
	)
}