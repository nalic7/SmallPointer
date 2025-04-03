VkSurfaceKHR m_vksurfacekhr = VK_NULL_HANDLE;

void vk_makeSurface()
{
	nali_info
	(
		"vkCreateWaylandSurfaceKHR %d",
		vkCreateWaylandSurfaceKHR
		(
			m_vkinstance,
			&(VkWaylandSurfaceCreateInfoKHR)
			{
				.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
				.display = m_wl_display_client_p,
				.surface = m_wl_surface_p,
		
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&m_vksurfacekhr
		)
	)
	m_surface_state |= NALI_SURFACE_C_S_CONFIG;
}

void vk_freeSurface()
{
	vkDestroySurfaceKHR(m_vkinstance, m_vksurfacekhr, NULL);
	m_vksurfacekhr = VK_NULL_HANDLE;
}