#ifndef _VK_H
	#define _VK_H

	//.c disable this to use all gpu
	#define _VK_SGPU
	//.c sc info
	#define _VK_INFO_SC

	#define _VK_VERSION VK_API_VERSION_1_0//VK_API_VERSION_1_0 VK_API_VERSION_1_4

	//.c surface
	#define _VK_COLOR_FORMAT_BYTE 4
	//.i surface
	#ifdef _CM_DRM
		#define _VK_COLOR_FORMAT VK_FORMAT_B8G8R8A8_UNORM
	#else
		#define _VK_COLOR_FORMAT VK_FORMAT_R8G8B8A8_UNORM
	#endif
	//.i image
	#define _VK_IMAGE_FORMAT VK_FORMAT_R8G8B8A8_UNORM
	#define _VK_COLOR_SPACE VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
	#define _VK_DEPTH_FORMAT VK_FORMAT_D32_SFLOAT//VK_FORMAT_D16_UNORM

	//.c sample
	#define _VK_SAMPLE_S VK_TRUE//VK_FALSE
	#define _VK_SAMPLE_C VK_SAMPLE_COUNT_8_BIT//VK_SAMPLE_COUNT_1_BIT
	#define _VK_SAMPLE_V 1.0F//0

	//.c vsync
	#define _VK_PRESENT VK_PRESENT_MODE_FIFO_KHR//VK_PRESENT_MODE_IMMEDIATE_KHR

	//.c sampler
	#define _VK_MAX_SAMPLER_ANISOTROPY 16.0F//0

	extern uint32_t _vk_device;
	extern uint32_t _vk_queue_g;
	extern uint32_t _vk_queue_ct;

	extern uint8_t _vk_non_coherent_atom_size;

	void _vk_set();
	void _vk_free();
#endif
