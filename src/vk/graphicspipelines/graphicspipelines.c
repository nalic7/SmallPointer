void vk_makeGraphicsPipelines(VulkanStructure& vulkanstructure, const VkVertexInputBindingDescription& vkvertexinputbindingdescription, const std::vector<VkVertexInputAttributeDescription>& vkvertexinputattributedescription_vector, const std::vector<unsigned char>& vertex_char_vector, const std::vector<unsigned char>& fragment_char_vector)
{
	VkShaderModule vertexshadermodule = vk_makeShaderModule(vertex_char_vector, vulkanstructure);
	VkShaderModule fragmentshadermodule = vk_makeShaderModule(fragment_char_vector, vulkanstructure);

	VkPipelineShaderStageCreateInfo vertexvkpipelineshaderstagecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = vertexshadermodule,
		.pName = "main",
		.pNext = VK_NULL_HANDLE,
		.flags = 0,
		.pSpecializationInfo = VK_NULL_HANDLE
	};

	VkPipelineShaderStageCreateInfo fragmentvkpipelineshaderstagecreateinfo{};
	fragmentvkpipelineshaderstagecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragmentvkpipelineshaderstagecreateinfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragmentvkpipelineshaderstagecreateinfo.module = fragmentshadermodule;
	fragmentvkpipelineshaderstagecreateinfo.pName = "main";

	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo[] =
	{
		vertexvkpipelineshaderstagecreateinfo,
		fragmentvkpipelineshaderstagecreateinfo
	};

	VkPipelineVertexInputStateCreateInfo vkpipelinevertexinputstatecreateinfo{};
	vkpipelinevertexinputstatecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	vkpipelinevertexinputstatecreateinfo.vertexBindingDescriptionCount = 1;
	vkpipelinevertexinputstatecreateinfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vkvertexinputattributedescription_vector.size());
	vkpipelinevertexinputstatecreateinfo.pVertexBindingDescriptions = &vkvertexinputbindingdescription;
	vkpipelinevertexinputstatecreateinfo.pVertexAttributeDescriptions = vkvertexinputattributedescription_vector.data();

	/*vkpipelinevertexinputstatecreateinfo.vertexBindingDescriptionCount = 0;
	vkpipelinevertexinputstatecreateinfo.vertexAttributeDescriptionCount = 0;*/

	VkPipelineInputAssemblyStateCreateInfo vkpipelineinputassemblystatecreateinfo{};
	vkpipelineinputassemblystatecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	vkpipelineinputassemblystatecreateinfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	vkpipelineinputassemblystatecreateinfo.primitiveRestartEnable = 0;

	VkViewport vkviewport{};
	vkviewport.x = 0.0F;
	vkviewport.y = 0.0F;
	vkviewport.width = (float)vulkanstructure.vulkanswapchainstructure.vkextent2d.width;
	vkviewport.height = (float)vulkanstructure.vulkanswapchainstructure.vkextent2d.height;
	vkviewport.minDepth = 0.0F;
	vkviewport.maxDepth = 1.0F;

	//this->vkviewport = vkviewport;

	VkRect2D vkrect2d{};
	vkrect2d.offset = { 0, 0 };
	vkrect2d.extent = vulkanstructure.vulkanswapchainstructure.vkextent2d;

	//this->vkrect2d = vkrect2d;

	VkPipelineViewportStateCreateInfo vkpipelineviewportstatecreateinfo{};
	vkpipelineviewportstatecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	vkpipelineviewportstatecreateinfo.viewportCount = 1;
	vkpipelineviewportstatecreateinfo.pViewports = &vkviewport;
	vkpipelineviewportstatecreateinfo.scissorCount = 1;
	vkpipelineviewportstatecreateinfo.pScissors = &vkrect2d;

	VkPipelineRasterizationStateCreateInfo vkpipelinerasterizationstatecreateinfo{};
	vkpipelinerasterizationstatecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	vkpipelinerasterizationstatecreateinfo.depthClampEnable = 0;
	vkpipelinerasterizationstatecreateinfo.rasterizerDiscardEnable = 0;
	vkpipelinerasterizationstatecreateinfo.polygonMode = VK_POLYGON_MODE_FILL;
	vkpipelinerasterizationstatecreateinfo.lineWidth = 1.0F;
	vkpipelinerasterizationstatecreateinfo.cullMode = VK_CULL_MODE_NONE;
	vkpipelinerasterizationstatecreateinfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	vkpipelinerasterizationstatecreateinfo.depthBiasEnable = 0;

	VkPipelineMultisampleStateCreateInfo vkpipelinemultisamplestatecreateinfo{};
	vkpipelinemultisamplestatecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	vkpipelinemultisamplestatecreateinfo.sampleShadingEnable = 0;
	vkpipelinemultisamplestatecreateinfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	vkpipelinemultisamplestatecreateinfo.alphaToCoverageEnable = 1;

	VkPipelineDepthStencilStateCreateInfo vkpipelinedepthstencilstatecreateinfo{};
	vkpipelinedepthstencilstatecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	vkpipelinedepthstencilstatecreateinfo.depthTestEnable = 1;
	vkpipelinedepthstencilstatecreateinfo.depthWriteEnable = 1;
	vkpipelinedepthstencilstatecreateinfo.depthCompareOp = VK_COMPARE_OP_LESS;
	vkpipelinedepthstencilstatecreateinfo.depthBoundsTestEnable = 0;
	vkpipelinedepthstencilstatecreateinfo.stencilTestEnable = 0;

	VkPipelineColorBlendAttachmentState vkpipelinecolorblendattachmentstate{};
	vkpipelinecolorblendattachmentstate.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	vkpipelinecolorblendattachmentstate.blendEnable = 1;
	vkpipelinecolorblendattachmentstate.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	vkpipelinecolorblendattachmentstate.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	vkpipelinecolorblendattachmentstate.colorBlendOp = VK_BLEND_OP_ADD;
	vkpipelinecolorblendattachmentstate.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	vkpipelinecolorblendattachmentstate.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	vkpipelinecolorblendattachmentstate.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo vkpipelinecolorblendstatecreateinfo{};
	vkpipelinecolorblendstatecreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	vkpipelinecolorblendstatecreateinfo.logicOpEnable = 0;
	vkpipelinecolorblendstatecreateinfo.logicOp = VK_LOGIC_OP_COPY;
	vkpipelinecolorblendstatecreateinfo.attachmentCount = 1;
	vkpipelinecolorblendstatecreateinfo.pAttachments = &vkpipelinecolorblendattachmentstate;
	vkpipelinecolorblendstatecreateinfo.blendConstants[0] = 0.0F;
	vkpipelinecolorblendstatecreateinfo.blendConstants[1] = 0.0F;
	vkpipelinecolorblendstatecreateinfo.blendConstants[2] = 0.0F;
	vkpipelinecolorblendstatecreateinfo.blendConstants[3] = 0.0F;

	vk_makePipelineLayout();

	VkGraphicsPipelineCreateInfo vkgraphicspipelinecreateinfo{};
	vkgraphicspipelinecreateinfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	vkgraphicspipelinecreateinfo.stageCount = 2;
	vkgraphicspipelinecreateinfo.pStages = vkpipelineshaderstagecreateinfo;
	vkgraphicspipelinecreateinfo.pVertexInputState = &vkpipelinevertexinputstatecreateinfo;
	vkgraphicspipelinecreateinfo.pInputAssemblyState = &vkpipelineinputassemblystatecreateinfo;
	vkgraphicspipelinecreateinfo.pViewportState = &vkpipelineviewportstatecreateinfo;
	vkgraphicspipelinecreateinfo.pRasterizationState = &vkpipelinerasterizationstatecreateinfo;
	vkgraphicspipelinecreateinfo.pMultisampleState = &vkpipelinemultisamplestatecreateinfo;
	vkgraphicspipelinecreateinfo.pDepthStencilState = &vkpipelinedepthstencilstatecreateinfo;
	vkgraphicspipelinecreateinfo.pColorBlendState = &vkpipelinecolorblendstatecreateinfo;
	vkgraphicspipelinecreateinfo.layout = vulkanstructure.vulkanpipelinestructure.vkpipelinelayout;
	vkgraphicspipelinecreateinfo.renderPass = vulkanstructure.vulkanpipelinestructure.vkrenderpass;
	vkgraphicspipelinecreateinfo.subpass = 0;
	vkgraphicspipelinecreateinfo.basePipelineHandle = 0;

	if (vkCreateGraphicsPipelines(vulkanstructure.vulkandevicestructure.vkdevice, 0, 1, &vkgraphicspipelinecreateinfo, nullptr, &vulkanstructure.vulkanpipelinestructure.vkpipeline) != VK_SUCCESS)
	{
		Logs::print("vkCreateGraphicsPipelines");
	}

	vkDestroyShaderModule(vulkanstructure.vulkandevicestructure.vkdevice, fragmentshadermodule, nullptr);
	vkDestroyShaderModule(vulkanstructure.vulkandevicestructure.vkdevice, vertexshadermodule, nullptr);
}
