void vk_makePipelineLayout()
{
	VkPipelineLayoutCreateInfo vkpipelinelayoutcreateinfo{};
	vkpipelinelayoutcreateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	vkpipelinelayoutcreateinfo.setLayoutCount = 1;
	vkpipelinelayoutcreateinfo.pSetLayouts = &vulkanstructure.vulkandescriptorstructure.vkdescriptorsetlayout;

	if (vkCreatePipelineLayout(vulkanstructure.vulkandevicestructure.vkdevice, &vkpipelinelayoutcreateinfo, nullptr, &vulkanstructure.vulkanpipelinestructure.vkpipelinelayout) != VK_SUCCESS)
	{
		Logs::print("vkCreatePipelineLayout");
	}
}
