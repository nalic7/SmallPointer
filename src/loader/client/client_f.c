void (*nlcf_data_fp[NALI_NLC_DATA_FP_SIZE])(uint8_t *) = {nlcf_sync_player, nlcf_add_model, nlcf_rm_model};

//pack
void nlcf_read_data(uint8_t *data_p)
{
	if (*data_p != 255)
	{
		nlcf_data_fp[*data_p](data_p + 1);
	}
}

void nlcf_sync_player(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	memcpy(lc_rt_array + id * (3 + 3), data_p, (3 + 3) * sizeof(float));
	data_p += (3 + 3) * sizeof(float);

	nlcf_read_data(data_p);
}

void nlcf_add_model(uint8_t *data_p)
{
	uint8_t m_id = *data_p;
	data_p += sizeof(uint8_t);

	uint16_t id = *data_p;
	data_p += sizeof(uint16_t);

	lc_m_p_array[m_id] = realloc(lc_m_p_array[m_id], sizeof(uint16_t) * (lc_m_bl_array[m_id] + 1));
	lc_m_rt_p_array[m_id] = realloc(lc_m_rt_p_array[m_id], sizeof(float) * (3 + 3) * (lc_m_bl_array[m_id] + 1));

	lc_m_p_array[m_id][lc_m_bl_array[m_id]] = id;
	memcpy(lc_m_rt_p_array[m_id] + lc_m_bl_array[m_id], data_p, sizeof(float) * (3 + 3));
	data_p += sizeof(float) * (3 + 3);

	++lc_m_bl_array[m_id];

	uint8_t animate = *data_p;
	data_p += sizeof(uint8_t);
	if (animate != 255)
	{
		uint8_t keyframe = *data_p;
		data_p += sizeof(uint8_t);
	}
	nlcf_read_data(data_p);
}

void nlc_sync_rt_entity(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	float rt_p[3+3];
	nlcf_read_data(data_p);
}

void nlc_sync_c_entity(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	float rt_p[4];
	nlcf_read_data(data_p);
}

void nlcf_rm_model(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	nlcf_read_data(data_p);
}