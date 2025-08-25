//.i linux
int main()
{
	// fp_read(NALI_F_HOME NALI_F_HOME_IMAGE "/0.png", &(long){});
	#ifdef _CM_DEBUG
		_db_set();
	#endif

//	//s0-test
//	//if u look to o on x0 y0 z0 to x1 y0 z0 p_h is 90d
//	float
//		u_t[3] = {0},
//
//		o_t[3] = {1, 0, 0},
//		
//		u_h = 0,
//		u_v = 0,
//		
//		o_h = NALI_M_D2R(90),
//		o_v = 0,
//		
//		u_hv[3] = {1, 0, 0};
//		// u_hv[3];
//
//	struct timespec time_start, time_end;
//	clock_gettime(CLOCK_MONOTONIC, &time_start);
//
//	// float p2o[] =
//	// {
//	// 	o_x - p_x,
//	// 	o_y - p_y,
//	// 	o_z - p_z,
//	// };
//	// float cos_theta = dot(p_hv, p2o);
//	// // float angle_rad = acosf(cos_theta);
//
//	// o_h = NALI_M_XZ2YAW(o_x, o_z);
//	// o_v = NALI_M_XZ2YAW(o_y, o_x);
//
//	// p_hv[0] = NALI_M_HV2X(o_h, o_v);
//	// p_hv[1] = NALI_M_V2Y(o_v);
//	// p_hv[2] = NALI_M_HV2Z(o_h, o_v);
//
//	// m_ray(o_t, u_t, );
//
//	//s1-keyframe
//	//problem can it be more smooth?
//	//delta not stable
//	//start to end always change
//	// float delta = 0.25F;
//	float delta = 0;
//	float start = 6;
//	// float start = 4;
//	float end = 5;
//	// float end = 6;
//	float min = 4;
//	float max_value = 7/*  + 1 */;
//	// float old_end = -1;
//	//need + extra value
//	//offset
//	//6 7 4 5 -> 6 4 5
//	// while (fabsf(start - end) > 0.0025F)
//	//case delta is stable 5f/sec
//	// float next;
//	// if (end != old_end)
//	// {
//	// 	if (start > end)
//	// 	{
//	// 		float extra = max_value - start + end + 1 - min;
//
//	// 		//use extra
//	// 		_DB_N2L("0")
//	// 		next = extra;
//	// 	}
//	// 	else
//	// 	{
//	// 		_DB_N2L("1")
//	// 		next = end - start;
//	// 	}
//	// }
//	// for (uint32_t rw = 0; rw < 4; ++rw)
//	// {
//	// 	_DB_N2L("x %f", start += next * delta)
//	// 	_DB_N2L("x -> %f", start = NALI_M_WRAP_F(start, min, max_value))
//	// }
//	//s2-test0
//	// for (uint32_t rw = 0; rw < 5; ++rw)
//	// {
//	// 	if (start > end)
//	// 	{
//	// 		float extra = max_value - start + end/*  + 1 */ - min;
//
//	// 		//use extra
//	// 		_DB_N2L("rw 0 %d", rw)
//	// 		_DB_N2L("extra 0 %f", extra)
//	// 		_DB_N2L("extra 1 %f", end - start)
//	// 		_DB_N2L("x %f", start += extra * delta)
//	// 		_DB_N2L("x -> %f", start = NALI_M_WRAP_F(start, min, max_value))
//	// 	}
//	// 	else
//	// 	{
//	// 		_DB_N2L("rw 1 %d", rw)
//	// 		_DB_N2L("extra 1 %f", end - start)
//	// 		_DB_N2L("x %f", start += (end - start) * delta)
//	// 	}
//
//	// 	delta += 0.25;
//	// }
//	//e2-test0
//	//this step need stable delta
//	// delta = 0.25;
//	// delta = 1/90.0F;
//	delta = NALI_LC_D;
//	float next;
//	uint8_t frame = 0;
//	if (start > end)
//	{
//		float extra = max_value - start + end - min;
//
//		_DB_N2L("0 next %f", next = extra * delta)
//	}
//	else
//	{
//		_DB_N2L("1 next %f", next = (end - start) * delta)
//	}
//	//1/delta or frame/sec
//	for (uint32_t rw = 0; rw < 1 / delta; ++rw)
//	{
//		_DB_N2L("f %d", ++frame)
//		if (frame == NALI_LC_MAX_F)
//		{
//			_DB_N2L("x %f", start = end)
//		}
//		else
//		{
//			_DB_N2L("x %f", start += next)
//		}
//		_DB_N2L("x -> %f", start = NALI_M_WRAP_F(start, min, max_value))
//	}
//	//e1-keyframe
//
//	clock_gettime(CLOCK_MONOTONIC, &time_end);
//
//	// // _DB_N2L("cos_theta %f", cos_theta)
//	// // // _DB_N2L("angle_rad %f", angle_rad)
//
//	// _DB_N2L("horizontal angle %f", o_h)
//	// _DB_N2L("horizontal angle (r2d) %f", NALI_M_R2D(o_h))
//
//	// _DB_N2L("vertical angle %f", o_v)
//	// _DB_N2L("vertical angle (r2d) %f", NALI_M_R2D(o_v))
//
//	// _DB_N2L("u_hv[0] %f", u_hv[0])
//	// _DB_N2L("u_hv[1] %f", u_hv[1])
//	// _DB_N2L("u_hv[2] %f", u_hv[2])
//
//	_DB_N2L("time_start_sec %ld", time_start.tv_sec)
//	_DB_N2L("time_start_nsec %ld", time_start.tv_nsec)
//
//	_DB_N2L("time_end_sec %ld", time_end.tv_sec)
//	_DB_N2L("time_end_nsec %ld", time_end.tv_nsec)
//
//	_DB_N2L("time_final_sec %f", time_end.tv_sec + (double)time_end.tv_nsec / 1e9 - time_start.tv_sec - (double)time_start.tv_nsec / 1e9)
//	_DB_N2L("time_final_nsec %ld", (time_end.tv_sec - time_start.tv_sec) * 1000000000L + time_end.tv_nsec - time_start.tv_nsec)
//
//	_db_free();
//	//e0-test

	#ifdef _CM_GEN
		g_write();
	#endif
	lb_set();
	#ifdef _CM_SERVER
		ls_set();
	#endif
	#ifdef _CM_CLIENT
		lc_set();

		_sf_wlc_set();
		_vk_set();
		//! switch to pipewire
		// al_set();
		lc_vk();
		thrd_sleep(&(struct timespec){.tv_sec = 60*60, .tv_nsec = 0}, NULL);
//		swlcsp_pointer = 0;
	#endif

	//lb_loop();
}
