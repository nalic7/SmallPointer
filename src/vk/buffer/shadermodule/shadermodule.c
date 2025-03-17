void vk_makeShaderModule(uint32_t device, uint32_t* uint32_t_p, uint32_t size, VkShaderModuleCreateFlags vkshadermodulecreateflags, VkShaderModule* vkshadermodule_p)
{
	VkShaderModuleCreateInfo vkshadermodulecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pCode = uint32_t_p,
		.codeSize = size,
		.pNext = VK_NULL_HANDLE,
		.flags = vkshadermodulecreateflags
	};
	vkCreateShaderModule(m_vkdevice_p[device], &vkshadermodulecreateinfo, VK_NULL_HANDLE, vkshadermodule_p);
}