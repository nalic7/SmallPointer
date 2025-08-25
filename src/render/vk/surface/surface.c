VkSurfaceKHR _vk_sf_khr = VK_NULL_HANDLE;

void _vk_sf_make()
{
	#ifdef _CM_ST_ANDROID
		while (sa_anativewindow_p == NULL)
		{
			_DB_N2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
		}
		_DB_R2L
		(
			"vkCreateAndroidSurfaceKHR %d",
			vkCreateAndroidSurfaceKHR
			(
				_vkq_dv_pscdv_it,
				&(VkAndroidSurfaceCreateInfoKHR)
				{
					.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
					.window = sa_anativewindow_p,
					.flags = 0,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&_vk_sf_khr
			)
		)
	#else
		while (!(_sf_state & _SF_S_SURFACE))
		{
			_DB_N2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
			_DB_N2L("_sf_state %d", _sf_state)
		}
		_DB_R2L
		(
			"vkCreateWaylandSurfaceKHR %d",
			vkCreateWaylandSurfaceKHR
			(
				_vkq_dv_pscdv_it,
				&(VkWaylandSurfaceCreateInfoKHR)
				{
					.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
					.display = _sf_wlc_dp_p,
					.surface = _sf_wlc_sf_p,
					.flags = 0,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&_vk_sf_khr
			)
		)
	#endif
}

void _vk_sf_free()
{
	vkDestroySurfaceKHR(_vkq_dv_pscdv_it, _vk_sf_khr, NULL);
	_vk_sf_khr = VK_NULL_HANDLE;
}
