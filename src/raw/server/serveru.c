struct SMPTRsU smptr_svuSu[SMPT_NWlU];

void smptr_svuMset()
{
}

void smptr_svuMsend(SMPT_NWtU u)
{
	memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, &smptr_svuSu[u], sizeof(struct SMPTRsU));
	smptr_svPnet[u].Lnet += sizeof(struct SMPTRsU);
}

void smptr_svuMread(SMPT_NWtU u)
{
	memcpy(&smptr_svuSu[u], smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, sizeof(struct SMPTRsU));
	smptr_svPnet[u].Lnet += sizeof(struct SMPTRsU);
}

void smptr_svuMfread()
{
	if (smptr_svPfile)
	{
		fread(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWlU, smptr_svPfile);
	}
	else
	{
		memset(smptr_svuSu, 0, sizeof(struct SMPTRsU) * SMPT_NWlU);
	}
}

void smptr_svuMfsend()
{
	fwrite(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWlU, smptr_svPfile);
}

void smptr_svuMfree()
{
}
