#ifndef NALI_VK_SURFACE_H
#define NALI_VK_SURFACE_H

extern VkSurfaceKHR vks_vksurfacekhr;

#ifdef C_NALI_S_ANDROID
	#define VK_makeSurface \
		while (sa_anativewindow_p == NULL) \
		{ \
			NALI_D_LOG("ANativeActivity_onCreate_sleep") \
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL); \
		} \
		NALI_D_INFO \
		( \
			"vkCreateAndroidSurfaceKHR %d", \
			vkCreateAndroidSurfaceKHR \
			( \
				vkqdpdi_vkinstance, \
				&(VkAndroidSurfaceCreateInfoKHR) \
				{ \
					.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR, \
					.window = sa_anativewindow_p, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&vks_vksurfacekhr \
			) \
		)
#else
	#define VK_makeSurface \
		NALI_D_INFO \
		( \
			"vkCreateWaylandSurfaceKHR %d", \
			vkCreateWaylandSurfaceKHR \
			( \
				vkqdpdi_vkinstance, \
				&(VkWaylandSurfaceCreateInfoKHR) \
				{ \
					.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR, \
					.display = wlc_wl_display_client_p, \
					.surface = wlc_wl_surface_p, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&vks_vksurfacekhr \
			) \
		) \
		s_surface_state |= NALI_SURFACE_C_S_CONFIG;
#endif

#define VK_freeSurface \
	vkDestroySurfaceKHR(vkqdpdi_vkinstance, vks_vksurfacekhr, NULL); \
	vks_vksurfacekhr = VK_NULL_HANDLE;

#endif