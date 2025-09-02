#ifndef SMPT_AR_MD_H
	#define SMPT_AR_MD_H

	#ifdef SMPT_CM_RAW
		#define SMPT_AR_MD_M_L smpt_r_ce_sd_sti_l
	#else
		//! server
		#define SMPT_AR_MD_M_L smpt_r_sv_md_
	#endif

	void smpt_ar_md_set();
	void smpt_ar_md_loop();
	void smpt_ar_md_free();
#endif
