void smpt_rd_vk_plMmake(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass vkrenderpass, VkPipelineLayout vkpipelinelayout, VkPipeline *vkpipeline_p)
{
	SMPT_RD_VK_PL_VTmIPBIDST(vkvertexinputbindingdescription)
	SMPT_RD_VK_PL_VTmIPATBDST(vkvertexinputattributedescription_array)
	SMPT_RD_VK_PL_VTmIPSACAIF(&vkvertexinputbindingdescription, vkvertexinputattributedescription_array, 2, vkpipelinevertexinputstatecreateinfo)

	SMPT_RD_VK_PL_IPmAEB_SACAIF(vkpipelineinputassemblystatecreateinfo)

	SMPT_RD_VK_PL_VPmSACAIF(vkpipelineviewportstatecreateinfo)

	SMPT_RD_VK_PL_RTITmSACAIF(vkpipelinerasterizationstatecreateinfo)
	SMPT_RD_VK_PL_MTmSPSACAIF(vkpipelinemultisamplestatecreateinfo)

	SMPT_RD_VK_PL_CLmBATMST(vkpipelinecolorblendattachmentstate)
	SMPT_RD_VK_PL_CLmBSACAIF(&vkpipelinecolorblendattachmentstate, vkpipelinecolorblendstatecreateinfo)

	SMPT_RD_VK_PL_DNMmSET(vkdynamicstate_array)
	SMPT_RD_VK_PL_DNMmSACAIF(vkdynamicstate_array, 2, vkpipelinedynamicstatecreateinfo)

	SMPT_RD_VK_PLDmSC_SACAIF(vkpipelinedepthstencilstatecreateinfo)

	SMPT_DBmR2L
	(
		"vkCreateGraphicsPipelines %d",
		vkCreateGraphicsPipelines
		(
			smpt_rd_vkq_dvP[device],
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
