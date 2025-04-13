void wlczwp_setPointer()
{
	if (m_zwp_locked_pointer_v1_p)
	{
		m_pointer_id = 0;

		zwp_locked_pointer_v1_destroy(m_zwp_locked_pointer_v1_p);
		m_zwp_locked_pointer_v1_p = NULL;

		zwp_relative_pointer_v1_destroy(m_zwp_relative_pointer_v1_p);
		m_zwp_relative_pointer_v1_p = NULL;
	}
	else
	{
		m_pointer_id = 255;

		nali_info("zwp_pointer_constraints_v1_lock_pointer %p", m_zwp_locked_pointer_v1_p = zwp_pointer_constraints_v1_lock_pointer(m_zwp_pointer_constraints_v1_p, m_wl_surface_p, m_wl_pointer_p, NULL, ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT))
		nali_info("zwp_locked_pointer_v1_add_listener %d", zwp_locked_pointer_v1_add_listener(m_zwp_locked_pointer_v1_p, &m_zwp_locked_pointer_v1_listener, NULL))

		nali_info("zwp_relative_pointer_manager_v1_get_relative_pointer %p", m_zwp_relative_pointer_v1_p = zwp_relative_pointer_manager_v1_get_relative_pointer(m_zwp_relative_pointer_manager_v1_p, m_wl_pointer_p))
		nali_info("zwp_relative_pointer_v1_add_listener %d", zwp_relative_pointer_v1_add_listener(m_zwp_relative_pointer_v1_p, &m_zwp_relative_pointer_v1_listener, NULL))
	}
}