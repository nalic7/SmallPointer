#ifndef SMPTRhCE
	#define SMPTRhCE

	extern uint8_t smptr_cePnet[SMPTRlNET];
	extern SMPTRtNET smptr_ceLnet;

	void smptr_ceMset();
	void smptr_ceMsend();
	void smptr_ceMread();
	void smptr_ceMfree(uint32_t device);
#endif
