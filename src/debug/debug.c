mtx_t *m_mtx_t_print_p = &(mtx_t){};

void debug_init()
{
	mtx_init(m_mtx_t_print_p, mtx_plain);
}

void debug_free()
{
	mtx_destroy(m_mtx_t_print_p);
}