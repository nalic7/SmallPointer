VkSurfaceKHR m_vksurfacekhr = VK_NULL_HANDLE;

void vk_makeSurface()
{
	do
	{
		info("wait_vk_wl")
		struct timespec ts = {1, 0};
		thrd_sleep(&ts, NULL);
		info("surface_wait %d", (m_surface_state & NALI_SURFACE_C_S_CONFIG + NALI_SURFACE_C_S_WAIT) == NALI_SURFACE_C_S_WAIT)
	} while ((m_surface_state & NALI_SURFACE_C_S_CONFIG + NALI_SURFACE_C_S_WAIT) == NALI_SURFACE_C_S_WAIT);

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

void vk_freeSurface()
{
	vkDestroySurfaceKHR(m_vkinstance, m_vksurfacekhr, NULL);
	m_vksurfacekhr = VK_NULL_HANDLE;
}