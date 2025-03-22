void vk_setVkPipelineShaderStageCreateInfo(uint32_t device, uint32_t vert, uint32_t frag, VkPipelineShaderStageCreateFlags vkpipelineshaderstagecreateflags_vert, VkPipelineShaderStageCreateFlags vkpipelineshaderstagecreateflags_frag, VkShaderModule *vkshadermodule_vert_p, VkShaderModule *vkshadermodule_frag_p, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p)
{
	const char *shader_folder = "../asset/shader/";
	const char *vert_folder = "vert/";
	const char *frag_folder = "frag/";
	const char *spv_file = ".spv";

	char *vert_file_name = math_get(vert);
	char *frag_file_name = math_get(frag);

	char *c0 = math_combine(shader_folder, vert_folder);
	char *c1 = math_combine(c0, vert_file_name);
	free(c0);
	char *c2 = math_combine(c1, spv_file);
	free(c1);

	uint32_t size = 0;
	uint32_t *uint32_t_p = file_uint32_t(c2, &size);
	free(c2);

	vk_makeShaderModule(device, uint32_t_p, size, 0, vkshadermodule_vert_p);
	free(uint32_t_p);

	c0 = math_combine(shader_folder, frag_folder);
	c1 = math_combine(c0, frag_file_name);
	free(c0);
	c2 = math_combine(c1, spv_file);
	free(c1);

	uint32_t_p = file_uint32_t(c2, &size);
	free(c2);

	vk_makeShaderModule(device, uint32_t_p, size, 0, vkshadermodule_frag_p);
	free(uint32_t_p);

	free(vert_file_name);
	free(frag_file_name);

	vkpipelineshaderstagecreateinfo_p[0] = (VkPipelineShaderStageCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = *vkshadermodule_vert_p,
		.pName = "main",

		.flags = vkpipelineshaderstagecreateflags_vert,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
	vkpipelineshaderstagecreateinfo_p[1] = (VkPipelineShaderStageCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = *vkshadermodule_frag_p,
		.pName = "main",

		.flags = vkpipelineshaderstagecreateflags_frag,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
}