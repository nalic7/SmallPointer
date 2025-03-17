void vk_setVkPipelineShaderStageCreateInfo(uint32_t device, VkPipelineShaderStageCreateFlags vkpipelineshaderstagecreateflags_vert, VkPipelineShaderStageCreateFlags vkpipelineshaderstagecreateflags_frag, VkShaderModule* vkshadermodule_vert_p, VkShaderModule* vkshadermodule_frag_p, VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_array[])
{
	uint32_t size = 0;
	uint32_t* uint32_t_p = file_uint32_t("../asset/vert.spv", &size);
	vk_makeShaderModule(device, uint32_t_p, size, 0, vkshadermodule_vert_p);
	free(uint32_t_p);

	uint32_t_p = file_uint32_t("../asset/frag.spv", &size);
	vk_makeShaderModule(device, uint32_t_p, size, 0, vkshadermodule_frag_p);
	free(uint32_t_p);

	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_vert =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = *vkshadermodule_vert_p,
		.pName = "main",

		.flags = vkpipelineshaderstagecreateflags_vert,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_frag =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = *vkshadermodule_frag_p,
		.pName = "main",

		.flags = vkpipelineshaderstagecreateflags_frag,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
	vkpipelineshaderstagecreateinfo_array[0] = vkpipelineshaderstagecreateinfo_vert;
	vkpipelineshaderstagecreateinfo_array[1] = vkpipelineshaderstagecreateinfo_frag;
}