#ifndef SMPT_RD_VK_PLhVT
	#define SMPT_RD_VK_PLhVT

	#define SMPT_RD_VK_PL_VTmIPBIDST(name) \
		VkVertexInputBindingDescription name = \
		{ \
			.binding = 0, \
			.stride = sizeof(float) * 3 + sizeof(uint32_t), \
			.inputRate = VK_VERTEX_INPUT_RATE_VERTEX \
		};

	#define SMPT_RD_VK_PL_VTmIPATBDST(name) \
		VkVertexInputAttributeDescription name[] = \
		{ \
			(VkVertexInputAttributeDescription) \
			{ \
				.binding = 0, \
				.location = 0, \
				.format = VK_FORMAT_R32G32B32_SFLOAT, \
				.offset = 0 \
			}, \
			(VkVertexInputAttributeDescription) \
			{ \
				.binding = 0, \
				.location = 1, \
				.format = VK_FORMAT_R32_UINT, \
				.offset = sizeof(float) * 3 \
			} \
		};

	#define SMPT_RD_VK_PL_VTmIPSACAIF(vkvertexinputbindingdescription_p, vkvertexinputattributedescription_p, vkvertexinputattributedescription_size, name) \
		VkPipelineVertexInputStateCreateInfo name = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, \
			.vertexBindingDescriptionCount = 1, \
			.pVertexBindingDescriptions = vkvertexinputbindingdescription_p, \
			.vertexAttributeDescriptionCount = vkvertexinputattributedescription_size, \
			.pVertexAttributeDescriptions = vkvertexinputattributedescription_p, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
