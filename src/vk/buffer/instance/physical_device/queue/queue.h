#ifndef NALI_VK_QUEUE_H
#define NALI_VK_QUEUE_H

// typedef struct
// {
//	 unsigned char graphics_size;
//	 // compute_size,
//	 // transfer_size,
//	 // sparse_binding_size,
//	 // protected_size,
//	 // video_decode_size,
//	 // video_encode_size,
//	 // optical_flow_size,
//	 // flag_size;
//	 // char set;
//	 uint32_t* graphics;
//	 // compute,
//	 // transfer,
//	 // sparse_binding,
//	 // protected,
//	 // video_decode,
//	 // video_encode,
//	 // optical_flow,
//	 // flag;
// } QueueList;

void vk_makeQueue(uint32_t device);

#endif
