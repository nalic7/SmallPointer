#ifndef _RD_VK_H
	#define _RD_VK_H

	//.c sc info
	#define _RD_VK_INFO_SC

	#define _RD_VK_VERSION VK_API_VERSION_1_0//VK_API_VERSION_1_0 VK_API_VERSION_1_4

	//.c surface
	#define _RD_VK_COLOR_FORMAT_BYTE 4
	//.i surface
	#ifdef _CM_DRM
		#define _RD_VK_COLOR_FORMAT VK_FORMAT_B8G8R8A8_UNORM
	#else
		#define _RD_VK_COLOR_FORMAT VK_FORMAT_R8G8B8A8_UNORM
	#endif
	//.i image
	#define _RD_VK_IMAGE_FORMAT VK_FORMAT_R8G8B8A8_UNORM
	#define _RD_VK_COLOR_SPACE VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
	#define _RD_VK_DEPTH_FORMAT VK_FORMAT_D32_SFLOAT//VK_FORMAT_D16_UNORM

	//.c sample
	#define _RD_VK_SAMPLE_S VK_TRUE//VK_FALSE
	#define _RD_VK_SAMPLE_C VK_SAMPLE_COUNT_8_BIT//VK_SAMPLE_COUNT_1_BIT
	#define _RD_VK_SAMPLE_V 1.0F//0

	//.c vsync
	#define _RD_VK_PRESENT VK_PRESENT_MODE_FIFO_KHR//VK_PRESENT_MODE_IMMEDIATE_KHR

	//.c sampler
	#define _RD_VK_MAX_SAMPLER_ANISOTROPY 16.0F//0

	extern uint32_t _rd_vk_device;
	extern uint32_t _rd_vk_queue_g;
	extern uint32_t _rd_vk_queue_ct;

	extern uint8_t _rd_vk_non_coherent_atom_size;

	void _rd_vk_set();
	void _rd_vk_free();
#endif
