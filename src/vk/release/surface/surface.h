#ifndef NALI_VK_SURFACE_H
#define NALI_VK_SURFACE_H

extern VkSurfaceKHR m_vksurfacekhr;

#ifdef NALI_S_ANDROID
	#define VK_makeSurface \
		while (m_anativewindow_p == NULL) \
		{ \
			nali_log("ANativeActivity_onCreate_sleep") \
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL); \
		} \
		nali_info \
		( \
			"vkCreateAndroidSurfaceKHR %d", \
			vkCreateAndroidSurfaceKHR \
			( \
				m_vkinstance, \
				&(VkAndroidSurfaceCreateInfoKHR) \
				{ \
					.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR, \
					.window = m_anativewindow_p, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&m_vksurfacekhr \
			) \
		)
#else
	#define VK_makeSurface \
		nali_info \
		( \
			"vkCreateWaylandSurfaceKHR %d", \
			vkCreateWaylandSurfaceKHR \
			( \
				m_vkinstance, \
				&(VkWaylandSurfaceCreateInfoKHR) \
				{ \
					.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR, \
					.display = m_wl_display_client_p, \
					.surface = m_wl_surface_p, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&m_vksurfacekhr \
			) \
		) \
		m_surface_state |= NALI_SURFACE_C_S_CONFIG;
#endif

#define VK_freeSurface \
	vkDestroySurfaceKHR(m_vkinstance, m_vksurfacekhr, NULL); \
	m_vksurfacekhr = VK_NULL_HANDLE;

#endif