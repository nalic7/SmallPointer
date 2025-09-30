uint32_t smpt_rd_vk_bfMtype(uint32_t Udevice, uint32_t Utypefilter, VkMemoryPropertyFlags Uvkmemorypropertyflags)
{
	VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdvP[Udevice];
	VkPhysicalDeviceMemoryProperties vkphysicaldevicememoryproperties;
	vkGetPhysicalDeviceMemoryProperties(vkphysicaldevice, &vkphysicaldevicememoryproperties);

	for (uint32_t t = 0; t < vkphysicaldevicememoryproperties.memoryTypeCount; ++t)
	{
		if ((Utypefilter & (1 << t)) && (vkphysicaldevicememoryproperties.memoryTypes[t].propertyFlags & Uvkmemorypropertyflags) == Uvkmemorypropertyflags)
		{
			return t;
		}
	}

	return 0;
}
