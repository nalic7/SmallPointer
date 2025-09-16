#ifndef SMPTRhCEA
	#define SMPTRhCEA

	#ifdef SMPT_CM_VK
		extern VkDescriptorSet *smptr_ceaPvkdescriptorset;
		extern VkBuffer *smptr_ceaPvkbuffer;
	#endif

	extern uint32_t smptr_ceaLa1;

	void smptr_ceaMset();
	void smptr_ceaMread();
	void smptr_ceaMloop();
	void smptr_ceaMfree();
#endif
