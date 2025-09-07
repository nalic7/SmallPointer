#ifndef SMPTR_CEMh
	#define SMPTR_CEMh

	#ifdef SMPT_CM_VK
		extern VkDescriptorSet *smptr_cemPvkdescriptorset;

		extern VkBuffer *smptr_cemPvkbuffer;
	#endif

	struct SMPTR_CEMsM1
	{
		SMPTRtMI i;
		SMPTRtMA a;
		SMPTRtMB b;
		SMPTRtMD d;
	};
	extern struct SMPTR_CEMsM1 *smptr_cemPm1;
	extern uint32_t smptr_cemLm1;

	void smptr_cemMset();
	void smptr_cemMread();
	void smptr_cemMfree();
#endif
