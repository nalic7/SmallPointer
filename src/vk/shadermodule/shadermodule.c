void vk_makeShaderModule(uint32_t device, uint32_t *uint32_t_ptr, uint32_t size, VkShaderModule* vkshadermodule_ptr)
{
	VkShaderModuleCreateInfo vkshadermodulecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pCode = uint32_t_ptr,
		.codeSize = size,
		.pNext = VK_NULL_HANDLE,
		.flags = 0
	};
	vkCreateShaderModule(m_vkdevice_ptr[device], &vkshadermodulecreateinfo, VK_NULL_HANDLE, vkshadermodule_ptr);
}
