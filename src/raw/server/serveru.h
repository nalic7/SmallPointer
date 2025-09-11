#ifndef SMPTRhSVU
	#define SMPTRhSVU

	extern struct SMPTRsU smptr_svuSu[SMPT_NWuU];
	extern uint8_t smpt_svuPinput[SMPT_NWuU][SMPT_IPuL];

	void smptr_svuMset();
	void smptr_svuMsend(SMPT_NWtU u);
	void smptr_svuMread(SMPT_NWtU u);
	void smptr_svuMfread();
	void smptr_svuMfsend();
	void smptr_svuMfree();
#endif
