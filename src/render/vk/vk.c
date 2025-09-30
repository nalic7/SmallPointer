
void smpt_rd_vkMset()
{
	smpt_rd_vkq_psc_itMset();
	#ifdef SMPT_CM_VK_DEBUG
		smpt_rd_vk_dbMset();
	#endif
	smpt_rd_vkq_pscMset();
	smpt_rd_vk_sfMmake();
	smpt_rd_vkqMset();

	smpt_rd_vk_cmpMset();
	smpt_rd_vk_swcMmake(smpt_rd_vkqPmax_queue_surface[smpt_rd_vkUdevice] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);

	while (!(smpt_sfUstate & SMPT_SFuS_RAW))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	smptr_ce_mdMvk();
	smptr_ceaMvk();
	smpt_rd_vkw_dsts_loMmake();
	smpt_rd_vkw_dstspMmake();

	smpt_rd_vk_cmdMset();
	SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, smpt_rd_vk_cmdMloop, NULL))
}

void smpt_rd_vkMfree()
{
	smpt_rd_vk_cmpMfree();
	smpt_rd_vk_swcMfree();

	smpt_rd_vkqMfree();
	smpt_rd_vk_sfMfree();
	smpt_rd_vkq_pscMfree();
	#ifdef SMPT_CM_VK_DEBUG
		smpt_rd_vk_dbMfree();
	#endif
	smpt_rd_vkq_psc_itMfree();
}
