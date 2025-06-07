#ifdef C_NALI_S_ANDROID
static float
	x00 = 0, y00 = 0,
	x01 = 0, y01 = 0;

static int s1_set(void *p)
{
	#ifdef C_NALI_CLIENT
		lb_set();
		lc_set();
		vk_set();
		al_set();
		lc_vk();
		lb_free();
	#endif

	while (1)
	{
		AInputEvent *ainputevent_p = NULL;
		while (sa_ainputqueue_p != NULL && AInputQueue_getEvent(sa_ainputqueue_p, &ainputevent_p) >= 0)
		{
			if (AInputQueue_preDispatchEvent(sa_ainputqueue_p, ainputevent_p))
			{
				continue;
			}
			if (AInputEvent_getType(ainputevent_p) == AINPUT_EVENT_TYPE_MOTION)
			{
				size_t pointer_count = AMotionEvent_getPointerCount(ainputevent_p);
//				if (pointer_count == 1)
//				{
//					NALI_D_LOG("AINPUT_EVENT_TYPE_MOTION")
				int32_t action = AMotionEvent_getAction(ainputevent_p);
				int32_t actionType = action & AMOTION_EVENT_ACTION_MASK;

				float l_x = AMotionEvent_getX(ainputevent_p, 0);
				float l_y = AMotionEvent_getY(ainputevent_p, 0);

				if (actionType == AMOTION_EVENT_ACTION_MOVE)
				{
					s_pointer_x = l_x - x00;
					s_pointer_y = l_y - y00;
				}
//					else if (/*actionType == AMOTION_EVENT_ACTION_DOWN || */actionType == AMOTION_EVENT_ACTION_UP)
//					{
//
//					}
				x00 = l_x;
				y00 = l_y;
//				}

				if (pointer_count == 2)
				{
					l_x = AMotionEvent_getX(ainputevent_p, 1);
					l_y = AMotionEvent_getY(ainputevent_p, 1);

					if (actionType == AMOTION_EVENT_ACTION_MOVE)
					{
						float l_x01 = l_x - x01;
						float l_y01 = l_y - y01;

						if (l_y01 < -2.0F)
						{
							s_key |= NALI_KEY_W;
							s_key &= 0xFFu - NALI_KEY_S;
						}
						else if (l_y01 > 2.0F)
						{
							s_key |= NALI_KEY_S;
							s_key &= 0xFFu - NALI_KEY_W;
						}

						if (l_x01 < -2.0F)
						{
							s_key |= NALI_KEY_A;
							s_key &= 0xFFu - NALI_KEY_D;
						}
						else if (l_x01 > 2.0F)
						{
							s_key |= NALI_KEY_D;
							s_key &= 0xFFu - NALI_KEY_A;
						}
					}

					x01 = l_x;
					y01 = l_y;
				}
				else
				{
					s_key &= 0xFFu - NALI_KEY_W - NALI_KEY_S - NALI_KEY_A - NALI_KEY_D;
				}
			}
			AInputQueue_finishEvent(sa_ainputqueue_p, ainputevent_p, 1);
		}
	}
	return 0;
}
//JNIEXPORT void JNICALL Java_com_nali_scene_Scene_runC(JNIEnv *jnienv_p, jobject jobject)
#else

int main()
{
	// fp_read(NALI_F_HOME NALI_F_HOME_IMAGE "/0.png", &(long){});
	#ifdef NALI_D_FILE
		d_set();
	#endif

	#ifdef C_NALI_GEN
		g_write();
	#endif
	#if C_NALI_SERVER
		nls_set();
	#endif
	#ifdef C_NALI_CLIENT
		nlc_set();
		//need test network
		// lb_set();
		// lc_set();
		// wlc_set();
		// vk_set();
		// al_set();
		// lc_vk();
		// lb_free();
		// s_pointer_id = 0;
	#endif

	lb_loop();
}
#endif