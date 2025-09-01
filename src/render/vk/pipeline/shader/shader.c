void _rd_vk_pl_sd_set(uint32_t device, char *vert_p, char *frag_p, VkShaderModule *vkshadermodule_vert_p, VkShaderModule *vkshadermodule_frag_p, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p)
{
	uint32_t code_b = 0;
	void *code_p = f_read(vert_p, &code_b);
	_DB_R2L
	(
		"vkCreateShaderModule %d",
		vkCreateShaderModule
		(
			_rd_vkq_dv_p[device],
			&(VkShaderModuleCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
				.pCode = code_p,
				.codeSize = code_b,
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkshadermodule_vert_p
		)
	)
	free(code_p);

	code_p = f_read(frag_p, &code_b);
	_DB_R2L
	(
		"vkCreateShaderModule %d",
		vkCreateShaderModule
		(
			_rd_vkq_dv_p[device],
			&(VkShaderModuleCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
				.pCode = code_p,
				.codeSize = code_b,
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkshadermodule_frag_p
		)
	)
	free(code_p);

	vkpipelineshaderstagecreateinfo_p[0] = (VkPipelineShaderStageCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = *vkshadermodule_vert_p,
		.pName = "main",

		.flags = 0,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
	vkpipelineshaderstagecreateinfo_p[1] = (VkPipelineShaderStageCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = *vkshadermodule_frag_p,
		.pName = "main",

		.flags = 0,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
}
