#ifndef NALI_VK_QUEUE_H
#define NALI_VK_QUEUE_H

extern uint32_t *m_max_queue_p;
// extern int32_t **m_queue_p;
extern uint32_t *m_max_queue_surface_p;
extern uint32_t **m_queue_surface_p;

extern VkQueue **m_vkqueue_p;

void vk_initQueue();
void vk_setQueue(uint32_t device);
void vk_getQueue(uint32_t device);
void vk_freeQueue();

#endif