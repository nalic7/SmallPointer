#ifndef SMPTRhSVM
	#define SMPTRhSVM

	extern struct SMPTRsM *smptr_svmPm;
	extern SMPTRtM smptr_svmLm;

	void smptr_svmMset();
	void smptr_svmMloop();
	void smptr_svmMsend(SMPT_NWtU u);
	void smptr_svmMfree();
#endif
