#ifndef SMPT_RD_VKhW
	#define SMPT_RD_VKhW

	#define SMPT_RD_VKWmDSTS(bind, Pvkdescriptorimageinfo, Pvkdescriptorbufferinfo, vkdescriptortype, vkdescriptorset, Pvkwritedescriptorset) \
		Pvkwritedescriptorset = (VkWriteDescriptorSet) \
		{ \
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, \
			.dstSet = vkdescriptorset, \
			.dstBinding = bind, \
			.dstArrayElement = 0, \
			.descriptorType = vkdescriptortype, \
			.descriptorCount = 1, \
			.pImageInfo = Pvkdescriptorimageinfo, \
			.pBufferInfo = Pvkdescriptorbufferinfo, \
			.pTexelBufferView = VK_NULL_HANDLE, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
