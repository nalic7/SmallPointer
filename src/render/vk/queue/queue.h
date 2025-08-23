#ifndef _VK_QUEUE_H
#define _VK_QUEUE_H

extern uint32_t *vkq_max_queue_p;
// extern int32_t **m_queue_p;
extern uint32_t *vkq_max_queue_surface_p;
extern uint32_t **vkq_queue_surface_p;

extern VkQueue **vkq_vkqueue_p;

void vkq_set();
void vkq_setQueue(uint32_t device);
void vkq_getQueue(uint32_t device);
void vkq_free();

#endif