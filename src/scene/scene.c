#ifdef NALI_S_ANDROID
static float
	x00 = 0, y00 = 0,
	x01 = 0, y01 = 0;

static int init(void *arg)
{
	#ifdef NALI_CLIENT
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
//					nali_log("AINPUT_EVENT_TYPE_MOTION")
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
void scene_set()
{
	nali_log("scene")
	nali_info("thrd_create %d", thrd_create(&(thrd_t){}, init, NULL))
}
#else

int main()
{
	// fp_read(NALI_HOME NALI_HOME_IMAGE "/0.png", &(long){});
	// #ifdef NALI_DEBUG
	// 	debug_init();
	// #endif

	#ifdef NALI_GEN
		g_write();
	#endif
	#ifdef NALI_CLIENT
		lb_set();
		lc_set();
		wlc_set();
		vk_set();
		al_set();
		lc_vk();
		lb_free();
		// nwc_init();
		s_pointer_id = 0;
	#endif
	#if NALI_SERVER
		// nws_init();
	#endif

	#if NALI_SERVER || NALI_CLIENT
		char *char_p = NULL;
		size_t size = 0;
		while (1)
		{
			nali_info_t("getline %ld", getline(&char_p, &size, stdin))

			#ifdef NALI_CLIENT
			if (!strcmp(char_p, "c\n"))
			{
				uint8_t size = sizeof(uint16_t) + 1;
				char *message = malloc(size);
				((uint16_t*)message)[0] = 1;
				message[sizeof(uint16_t)] = 'c';
				nali_info("send %ld", send(m_client_socket, message, size, 0))
				nali_log("%s", strerror(errno))
			}
			else if (!strcmp(char_p, "cq\n"))
			{
				m_net_client_state |= NALI_NET_CLIENT_FAIL;
			}
			#endif
			#if NALI_SERVER
				#ifdef NALI_CLIENT
			else if
				#else
			if
				#endif
			(!strcmp(char_p, "sq\n"))
			{
				m_net_server_state |= NALI_NET_SERVER_FAIL;
			}
			// #ifdef NALI_DEBUG
			// if (!strcmp(char_p, "dq\n"))
			// {
			// 	debug_free();
			// }
			// #endif

			// 	exit(EXIT_SUCCESS);

			#endif

			free(char_p);
			char_p = NULL;
			size = 0;
		}
	#endif
}
#endif