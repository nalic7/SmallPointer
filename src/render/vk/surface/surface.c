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
		#ifdef _CM_DRM
			uint32_t display_count = 0;
			_DB_R2L("vkGetPhysicalDeviceDisplayPropertiesKHR %d", vkGetPhysicalDeviceDisplayPropertiesKHR(_vkq_dv_pscdv_p[_vk_device], &display_count, VK_NULL_HANDLE))
			VkDisplayPropertiesKHR *vkdisplaypropertieskhr_p = malloc(sizeof(VkDisplayPropertiesKHR) * display_count);
			_DB_R2L("vkGetPhysicalDeviceDisplayPropertiesKHR %d", vkGetPhysicalDeviceDisplayPropertiesKHR(_vkq_dv_pscdv_p[_vk_device], &display_count, vkdisplaypropertieskhr_p))
			_DB_N2L("display_count %d", display_count)
			for (uint32_t l_0 = 0; l_0 < display_count; ++l_0)
			{
				_DB_N2L("%d %s", l_0, vkdisplaypropertieskhr_p[l_0].displayName)
			}

			uint32_t display_mode_count = 0;
			_DB_R2L("vkGetDisplayModePropertiesKHR %d", vkGetDisplayModePropertiesKHR(_vkq_dv_pscdv_p[_vk_device], vkdisplaypropertieskhr_p[0].display, &display_mode_count, VK_NULL_HANDLE))
			VkDisplayModePropertiesKHR *vkdisplaymodepropertieskhr_p = malloc(sizeof(VkDisplayModePropertiesKHR) * display_mode_count);
			_DB_R2L("vkGetDisplayModePropertiesKHR %d", vkGetDisplayModePropertiesKHR(_vkq_dv_pscdv_p[_vk_device], vkdisplaypropertieskhr_p[0].display, &display_mode_count, vkdisplaymodepropertieskhr_p))
			_DB_N2L("display_mode_count %d", display_mode_count)
			for (uint32_t l_0 = 0; l_0 < display_mode_count; ++l_0)
			{
				_DB_N2L("width %d", vkdisplaymodepropertieskhr_p[l_0].parameters.visibleRegion.width)
				_DB_N2L("hieght %d", vkdisplaymodepropertieskhr_p[l_0].parameters.visibleRegion.height)
				_DB_N2L("refreshRate %d", vkdisplaymodepropertieskhr_p[l_0].parameters.refreshRate)
			}
			_sf_width = vkdisplaymodepropertieskhr_p[0].parameters.visibleRegion.width;
			_sf_height = vkdisplaymodepropertieskhr_p[0].parameters.visibleRegion.height;
			//.i project m4x4
			_sf_state |= _SF_S_RE;

			uint32_t plane_count = 0;
			_DB_R2L("vkGetPhysicalDeviceDisplayPlanePropertiesKHR %d", vkGetPhysicalDeviceDisplayPlanePropertiesKHR(_vkq_dv_pscdv_p[_vk_device], &plane_count, VK_NULL_HANDLE))
			VkDisplayPlanePropertiesKHR *vkdisplayplanepropertieskhr_p = malloc(sizeof(VkDisplayPlanePropertiesKHR) * plane_count);
			_DB_R2L("vkGetPhysicalDeviceDisplayPlanePropertiesKHR %d", vkGetPhysicalDeviceDisplayPlanePropertiesKHR(_vkq_dv_pscdv_p[_vk_device], &plane_count, vkdisplayplanepropertieskhr_p))
			_DB_N2L("plane_count %d", plane_count)

			uint32_t plane = UINT32_MAX;
			uint32_t stack_index = 0;
			for (uint32_t l_0 = 0; l_0 < plane_count; ++l_0)
			{
				if (!vkdisplayplanepropertieskhr_p[l_0].currentDisplay || vkdisplayplanepropertieskhr_p[l_0].currentDisplay == vkdisplaypropertieskhr_p[0].display)
				{
					plane = l_0;
					stack_index = vkdisplayplanepropertieskhr_p[l_0].currentStackIndex;
					break;
				}
			}

			_DB_R2L
			(
				"vkCreateDisplayPlaneSurfaceKHR %d",
				vkCreateDisplayPlaneSurfaceKHR
				(
					_vkq_dv_pscdv_it,
					&(VkDisplaySurfaceCreateInfoKHR)
					{
						.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR,
						.displayMode = vkdisplaymodepropertieskhr_p[0].displayMode,
						.planeIndex = plane,
						.planeStackIndex = stack_index,
						.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
						.globalAlpha = 0,
						.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
						.imageExtent = vkdisplaymodepropertieskhr_p[0].parameters.visibleRegion,
						.flags = 0,
						.pNext = VK_NULL_HANDLE
					},
					VK_NULL_HANDLE,
					&_vk_sf_khr
				)
			)
			free(vkdisplaypropertieskhr_p);
			free(vkdisplaymodepropertieskhr_p);
		#endif
		#ifdef _CM_WL
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
	#endif
}

void _vk_sf_free()
{
	vkDestroySurfaceKHR(_vkq_dv_pscdv_it, _vk_sf_khr, NULL);
	_vk_sf_khr = VK_NULL_HANDLE;
}
