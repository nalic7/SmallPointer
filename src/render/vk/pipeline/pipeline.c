void smpt_rd_vk_pl_make(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass vkrenderpass, VkPipelineLayout vkpipelinelayout, VkPipeline *vkpipeline_p)
{
	SMPT_RD_VK_PL_VT_IPBIDST(vkvertexinputbindingdescription)
	SMPT_RD_VK_PL_VT_IPATBDST(vkvertexinputattributedescription_array)
	SMPT_RD_VK_PL_VT_IPSACAIF(&vkvertexinputbindingdescription, vkvertexinputattributedescription_array, 2, vkpipelinevertexinputstatecreateinfo)

	SMPT_RD_VK_PL_IP_AEB_SACAIF(vkpipelineinputassemblystatecreateinfo)

	SMPT_RD_VK_PL_VP_SACAIF(vkpipelineviewportstatecreateinfo)

	SMPT_RD_VK_PL_RTIT_SACAIF(vkpipelinerasterizationstatecreateinfo)
	SMPT_RD_VK_PL_MT_SPSACAIF(vkpipelinemultisamplestatecreateinfo)

	SMPT_RD_VK_PL_CL_BATMST(vkpipelinecolorblendattachmentstate)
	SMPT_RD_VK_PL_CL_BSACAIF(&vkpipelinecolorblendattachmentstate, vkpipelinecolorblendstatecreateinfo)

	SMPT_RD_VK_PL_DNM_SET(vkdynamicstate_array)
	SMPT_RD_VK_PL_DNM_SACAIF(vkdynamicstate_array, 2, vkpipelinedynamicstatecreateinfo)

	SMPT_RD_VK_PLD_SC_SACAIF(vkpipelinedepthstencilstatecreateinfo)

	SMPT_DB_R2L
	(
		"vkCreateGraphicsPipelines %d",
		vkCreateGraphicsPipelines
		(
			smpt_rd_vkq_dv_p[device],
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
