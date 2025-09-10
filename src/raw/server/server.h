#ifndef SMPTRhSV
	#define SMPTRhSV

	struct SMPTR_SVtNET
	{
		uint8_t Pnet[SMPTRlNET];
		SMPTRtNET Lnet;
	};
	extern struct SMPTR_SVtNET smptr_svPnet[SMPT_NWuU];

	void smptr_svMset();
	void smptr_svMsend(SMPT_NWtU u);
	void smptr_svMread();
	int smptr_svMloop(void *P);
	void smptr_svMfree();
#endif
