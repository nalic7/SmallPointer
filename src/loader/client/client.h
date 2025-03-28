#ifndef NALI_LOADER_CLIENT_H
#define NALI_LOADER_CLIENT_H

// typedef struct
// {
// 	//1-4
// 	uint8_t *i_p;
// 	uint32_t *i_size_p;
// 	uint8_t *i_byte_p;

// 	//3
// 	uint8_t *v_p;
// 	uint32_t *v_size_p;

// 	//4
// 	uint8_t *c_p;
// 	uint32_t *c_size_p;

// 	//2
// 	uint8_t *t_p;
// 	uint32_t *t_size_p;

// 	//3
// 	uint8_t *n_p;
// 	uint32_t *n_size_p;

// 	//1
// 	uint8_t *j_p;
// 	uint32_t *j_size_p;

// 	//4
// 	uint8_t *w_p;
// 	uint32_t *w_size_p;
// } nali_model;

// typedef struct
// {
// 	//2
// 	uint8_t *s_p;
// 	uint32_t *s_size_p;
// } nali_sound;

// typedef struct
// {
// 	uint32_t *width, *height;
// 	uint8_t
// 		*p_p,
// 		*state_p;//mipmap

// 	//width * height
// 	// uint32_t *p_size_p;
// } nali_texture;

extern VkBuffer **m_nali_g_index_vkbuffer_p;
extern VkBuffer **m_nali_g_data_vkbuffer_p;

extern uint16_t m_nali_g_max_image;
extern uint8_t *m_nali_g_image_state_uint8_t_p;

extern uint32_t *m_nali_g_image_wh_uint32_t_p;
extern VkImage *m_nali_g_image_vkimage_p;

extern uint8_t **m_nali_g_image_uint8_t_p;
extern VkBuffer *m_nali_g_image_vkbuffer_p;
extern VkDeviceMemory *m_nali_g_image_vkbuffer_vkdevicememory_p;

void lc_init();

void lc_initVK();
void lc_clearVK(uint32_t device);

void lc_setVkVertexInputBindingDescription(VkVertexInputBindingDescription *vkvertexinputbindingdescription_p);
void lc_setVkVertexInputAttributeDescription(VkVertexInputAttributeDescription *vkvertexinputattributedescription_p);

void lc_setVkDescriptorSetLayout(VkDescriptorSetLayout *vkdescriptorsetlayout_p);
void lc_setVkDescriptorPoolSize(VkDescriptorPoolSize *vkdescriptorpoolsize_p);
void lc_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkDescriptorImageInfo *vkdescriptorimageinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p);

#endif