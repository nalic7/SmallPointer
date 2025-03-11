void vk_makeSurface(VkWaylandSurfaceCreateFlagsKHR vkwaylandsurfacecreateflagskhr)
{
	VkWaylandSurfaceCreateInfoKHR vkwaylandsurfacecreateinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
		.display = m_wl_display,
		.surface = m_wl_surface,
		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	if (vkCreateWaylandSurfaceKHR(m_vkinstance, &vkwaylandsurfacecreateinfokhr, VK_NULL_HANDLE, &m_vksurfacekhr) != VK_SUCCESS)
	{
		error("vkCreateWaylandSurfaceKHR")
	}
}
