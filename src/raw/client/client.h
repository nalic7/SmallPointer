#ifndef SMPTRhCE
	#define SMPTRhCE

	//.c max fps/refresh rate
	#define _RC_MAX_F 144.0F
	#define _RC_D 1/_RC_MAX_F

	extern SMPTRB_PT lc_net_bl;
	extern uint8_t lc_net_p[SMPTRB_NET_BL];

	// extern float lc_delta;

	void lc_set();
	void lc_vk();
	void lc_read();
	void lc_free(uint32_t device);
#endif
