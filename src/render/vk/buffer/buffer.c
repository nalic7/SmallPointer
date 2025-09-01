uint32_t _rd_vk_bf_type(uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags)
{
	VkPhysicalDevice vkphysicaldevice = _rd_vkq_dv_pscdv_p[device];
	VkPhysicalDeviceMemoryProperties vkphysicaldevicememoryproperties;
	vkGetPhysicalDeviceMemoryProperties(vkphysicaldevice, &vkphysicaldevicememoryproperties);

	for (uint32_t t = 0; t < vkphysicaldevicememoryproperties.memoryTypeCount; ++t)
	{
		if ((typefilter & (1 << t)) && (vkphysicaldevicememoryproperties.memoryTypes[t].propertyFlags & vkmemorypropertyflags) == vkmemorypropertyflags)
		{
			return t;
		}
	}

	return 0;
}
