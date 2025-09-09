#ifndef SMPTRhCE
	#define SMPTRhCE

	extern SMPTRtNET smptr_ceLnet;
	extern uint8_t smptr_cePnet[SMPTRlNET];

	void smptr_ceMset();
	void smptr_ceMread();
	void smptr_ceMfree(uint32_t device);
#endif
