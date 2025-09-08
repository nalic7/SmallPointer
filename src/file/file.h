#ifndef SMPThF
	#define SMPThF

	#ifdef SMPT_CM_GEN
		//.c source folder
		#define NALI_F_FACTORY "../source/"
		#define NALI_F_FACTORY_MODEL NALI_F_FACTORY "model"
		#define NALI_F_FACTORY_KEYFRAME NALI_F_FACTORY "keyframe"
	#endif

	#ifdef SMPT_CM_ST_ANDROID
		#define NALI_F_HOME

		//.c package folder
		#define NALI_F_PACKAGE "/storage/emulated/0/Android/data/com.nali.smallpointer/"
		#define NALI_F_SAVE NALI_F_PACKAGE "save/"
		#define NALI_F_READ_CACHE NALI_F_PACKAGE "c"
	#else
		#define NALI_F_HOME "../asset/"
		#define NALI_F_SAVE "save/"
	#endif

	//! will clean this
	#define NALI_F_HOME_SOUND NALI_F_HOME "sound/"
	#define NALI_F_HOME_SOUND_BGM NALI_F_HOME_SOUND "bgm.ogg"

	// #define NALI_F_HOME_IMAGE NALI_F_HOME "image"

	#define NALI_F_HOME_ASSET NALI_F_HOME "asset.bin"
	#define NALI_F_HOME_VERT NALI_F_HOME "vert.spv"
	#define NALI_F_HOME_FRAG NALI_F_HOME "frag.spv"

	#define NALI_F_SAVE_LOG NALI_F_SAVE "log.dat"
	#define NALI_F_SAVE_SPACE NALI_F_SAVE "space.bin"

	// #define NALI_F_SAVE_USER NALI_F_SAVE "user/"
	// #define NALI_F_SAVE_USER_ITEM NALI_F_SAVE "user/item/"
	// #define NALI_F_SAVE_USER_TEAM NALI_F_SAVE "user/team/"

	// #define NALI_F_SAVE_MAP NALI_F_SAVE "map/"

	void *f_read(const char *c_p, uint32_t *bl_p);
	void *f_read1(FILE *file_p, uint32_t *bl_p);
#endif
