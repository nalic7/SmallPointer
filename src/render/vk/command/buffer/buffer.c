void smpt_rd_vk_cm_bfMset()
{
	for (uint32_t l0 = 0; l0 < smpt_rd_vkqLinfo; ++l0)
	{
		struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + l0;
		for (uint32_t l1 = 0; l1 < Pinfo->Sfamily.L; ++l1)
		{
			Pinfo->Pvkcommandbuffer = malloc(sizeof(VkCommandBuffer) * smpt_rd_vk_swcUimage);
			for (uint32_t l2 = 0; l2 < smpt_rd_vk_swcUimage; ++l2)
				SMPT_DBmR2L
				(
					"vkAllocateCommandBuffers %d",
					vkAllocateCommandBuffers
					(
						Pinfo->Vvkdevice,
						&(VkCommandBufferAllocateInfo)
						{
							.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
							.commandPool = Pinfo->Pvkcommandpool + l1,
							.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
							.commandBufferCount = 1,
							.pNext = VK_NULL_HANDLE
						},
						Pinfo->Pvkcommandbuffer + l1
					)
				)
		}
	}
}

void smpt_rd_vk_cm_bfMfree()
{
	for (uint32_t l0 = 0; l0 < smpt_rd_vkqLinfo; ++l0)
	{
		struct SMPT_RD_VKQsINFO Sinfo = smpt_rd_vkqPinfo[l0];
		for (uint32_t l1 = 0; l1 < Sinfo.Sfamily.L; ++l1)
			vkFreeCommandBuffer(Sinfo.Vvkdevice, Sinfo.Pvkcommandbuffer[l1], VK_NULL_HANDLE);
		free(Sinfo.Pvkcommandbuffer);
	}
}
