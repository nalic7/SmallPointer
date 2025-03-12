void vk_makeSurface(VkWaylandSurfaceCreateFlagsKHR vkwaylandsurfacecreateflagskhr)
{
	VkWaylandSurfaceCreateInfoKHR vkwaylandsurfacecreateinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
		.display = m_wl_display_client,
		.surface = m_wl_surface,
		.flags = vkwaylandsurfacecreateflagskhr,
		.pNext = VK_NULL_HANDLE
	};

	VkResult vkresult = vkCreateWaylandSurfaceKHR(m_vkinstance, &vkwaylandsurfacecreateinfokhr, VK_NULL_HANDLE, &m_vksurfacekhr);
	if (vkresult != VK_SUCCESS)
	{
		error("vkCreateWaylandSurfaceKHR %d", vkresult)
	}
}
