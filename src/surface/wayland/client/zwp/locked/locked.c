static void zwp_locked_pointer_v1_listener_locked(void *data, struct zwp_locked_pointer_v1 *zwp_locked_pointer_v1)
{

}

static void zwp_locked_pointer_v1_listener_unlocked(void *data, struct zwp_locked_pointer_v1 *zwp_locked_pointer_v1)
{

}

struct zwp_locked_pointer_v1_listener wlczwp_zwp_locked_pointer_v1_listener =
{
	.locked = zwp_locked_pointer_v1_listener_locked,
	.unlocked = zwp_locked_pointer_v1_listener_unlocked
};