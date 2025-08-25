void _vk_pl_make(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass vkrenderpass, VkPipelineLayout vkpipelinelayout, VkPipeline *vkpipeline_p)
{
	LCS_setVkVertexInputBindingDescription(vkvertexinputbindingdescription)
	LCS_setVkVertexInputAttributeDescription(vkvertexinputattributedescription_array)
	_VK_PL_VT_IPSACAIF(&vkvertexinputbindingdescription, vkvertexinputattributedescription_array, 2, vkpipelinevertexinputstatecreateinfo)

	_VK_PL_IP_AEB_SACAIF(vkpipelineinputassemblystatecreateinfo)

	_VK_PL_VP_SACAIF(vkpipelineviewportstatecreateinfo)

	_VK_PL_RTIT_SACAIF(vkpipelinerasterizationstatecreateinfo)
	_VK_PL_MT_SPSACAIF(vkpipelinemultisamplestatecreateinfo)

	_VK_PL_CL_BATMST(vkpipelinecolorblendattachmentstate)
	_VK_PL_CL_BSACAIF(&vkpipelinecolorblendattachmentstate, vkpipelinecolorblendstatecreateinfo)

	_VK_PL_DNM_SET(vkdynamicstate_array)
	_VK_PL_DNM_SACAIF(vkdynamicstate_array, 2, vkpipelinedynamicstatecreateinfo)

	_VK_PLD_SC_SACAIF(vkpipelinedepthstencilstatecreateinfo)

	_DB_R2L
	(
		"vkCreateGraphicsPipelines %d",
		vkCreateGraphicsPipelines
		(
			_vkq_dv_p[device],
			VK_NULL_HANDLE,
			1,
			&(VkGraphicsPipelineCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
				.stageCount = 2,
				.pStages = vkpipelineshaderstagecreateinfo_p,
				.pVertexInputState = &vkpipelinevertexinputstatecreateinfo,
				.pInputAssemblyState = &vkpipelineinputassemblystatecreateinfo,
				.pTessellationState = VK_NULL_HANDLE,
				.pViewportState = &vkpipelineviewportstatecreateinfo,
				.pRasterizationState = &vkpipelinerasterizationstatecreateinfo,
				.pMultisampleState = &vkpipelinemultisamplestatecreateinfo,
				.pDepthStencilState = &vkpipelinedepthstencilstatecreateinfo,
				.pColorBlendState = &vkpipelinecolorblendstatecreateinfo,
				.pDynamicState = &vkpipelinedynamicstatecreateinfo,
				.layout = vkpipelinelayout,
				.renderPass = vkrenderpass,
				.subpass = 0,
				.basePipelineHandle = VK_NULL_HANDLE,

				.basePipelineIndex = 0,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkpipeline_p
		)
	)
}
