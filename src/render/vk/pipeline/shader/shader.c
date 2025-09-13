void smpt_rd_vk_pl_sdMset(uint32_t device, char *Pvert, char *Pfrag, VkShaderModule *Pvkshadermodule_vert, VkShaderModule *Pvkshadermodule_frag, VkPipelineShaderStageCreateInfo *Pvkpipelineshaderstagecreateinfo)
{
	uint32_t code_b = 0;
	void *code_p = smptfMread(Pvert, &code_b);
	SMPT_DBmR2L
	(
		"vkCreateShaderModule %d",
		vkCreateShaderModule
		(
			smpt_rd_vkq_dvP[device],
			&(VkShaderModuleCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
				.pCode = code_p,
				.codeSize = code_b,
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			Pvkshadermodule_vert
		)
	)
	free(code_p);

	code_p = smptfMread(Pfrag, &code_b);
	SMPT_DBmR2L
	(
		"vkCreateShaderModule %d",
		vkCreateShaderModule
		(
			smpt_rd_vkq_dvP[device],
			&(VkShaderModuleCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
				.pCode = code_p,
				.codeSize = code_b,
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			Pvkshadermodule_frag
		)
	)
	free(code_p);

	Pvkpipelineshaderstagecreateinfo[0] = (VkPipelineShaderStageCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = *Pvkshadermodule_vert,
		.pName = "main",

		.flags = 0,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
	Pvkpipelineshaderstagecreateinfo[1] = (VkPipelineShaderStageCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = *Pvkshadermodule_frag,
		.pName = "main",

		.flags = 0,
		.pNext = VK_NULL_HANDLE,
		.pSpecializationInfo = VK_NULL_HANDLE
	};
}
