struct zwp_locked_pointer_v1 *_sf_wlc_zwp_lp_p = NULL;

static void zwp_locked_pointer_v1_listener_locked(void *data, struct zwp_locked_pointer_v1 *zwp_locked_pointer_v1)
{

}

static void zwp_locked_pointer_v1_listener_unlocked(void *data, struct zwp_locked_pointer_v1 *zwp_locked_pointer_v1)
{

}

struct zwp_locked_pointer_v1_listener _sf_wlc_zwp_lp_listener =
{
	.locked = zwp_locked_pointer_v1_listener_locked,
	.unlocked = zwp_locked_pointer_v1_listener_unlocked
};

void _sf_wlc_zwp_lp_free()
{
	if (_sf_wlc_zwp_lp_p)
	{
		zwp_locked_pointer_v1_destroy(_sf_wlc_zwp_lp_p);
		_sf_wlc_zwp_lp_p = NULL;
	}
}
