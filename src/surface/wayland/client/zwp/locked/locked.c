struct zwp_locked_pointer_v1 *s_wlc_zwp_lp_p = NULL;

static void zwp_locked_pointer_v1_listener_locked(void *data, struct zwp_locked_pointer_v1 *zwp_locked_pointer_v1)
{

}

static void zwp_locked_pointer_v1_listener_unlocked(void *data, struct zwp_locked_pointer_v1 *zwp_locked_pointer_v1)
{

}

struct zwp_locked_pointer_v1_listener s_wlc_zwp_lp_listener =
{
	.locked = zwp_locked_pointer_v1_listener_locked,
	.unlocked = zwp_locked_pointer_v1_listener_unlocked
};

void s_wlc_zwp_lp_free()
{
	if (s_wlc_zwp_lp_p)
	{
		zwp_locked_pointer_v1_destroy(s_wlc_zwp_lp_p);
		s_wlc_zwp_lp_p = NULL;
	}
}
