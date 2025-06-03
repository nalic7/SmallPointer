#define NALI_VD_M_POMI0 0
// #define NALI_VD_M_POMI1 1
// #define NALI_VD_M_POMI2 2
#define NALI_VD_M_STAR0 1
#define NALI_VD_M_LAND0 2

#define NALI_VD_M_MAX 3

extern uint8_t vd_m_bl_array[NALI_VD_M_MAX];
extern uint16_t *vd_m_p_array[NALI_VD_M_MAX];
extern float *vd_m_rt_p_array[NALI_VD_M_MAX];

extern mtx_t *vd_mtx_t_p;

void vd_set();
int vd_loop(void *arg);
void vd_free();