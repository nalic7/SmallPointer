void vk_makeSurface()
{
	while ((m_surface_state & NALI_SURFACE_C_S_CONFIG + NALI_SURFACE_C_S_WAIT) == NALI_SURFACE_C_S_WAIT)
	{
		info("wait_vk_wl")
		struct timespec ts = {1, 0};
		thrd_sleep(&ts, NULL);
	}

	VkWaylandSurfaceCreateInfoKHR vkwaylandsurfacecreateinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
		.display = m_wl_display_client_p,
		.surface = m_wl_surface_p,

		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	VkResult vkresult = vkCreateWaylandSurfaceKHR(m_vkinstance, &vkwaylandsurfacecreateinfokhr, VK_NULL_HANDLE, &m_vksurfacekhr);
	if (vkresult != VK_SUCCESS)
	{
		error("vkCreateWaylandSurfaceKHR %d", vkresult)
	}
}