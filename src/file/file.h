#ifndef NALI_FILE_H
#define NALI_FILE_H

#ifdef C_NALI_GEN
	#ifdef C_NALI_S_ANDROID
		#define NALI_FACTORY NALI_F_HOME
	#else
		#define NALI_F_FACTORY "../source/"
		#define NALI_F_FACTORY_MODEL NALI_F_FACTORY "model"
		#define NALI_F_FACTORY_KEYFRAME NALI_F_FACTORY "keyframe"
	#endif
#endif

#ifdef C_NALI_S_ANDROID
	#define NALI_F_HOME

	#define NALI_F_PACKAGE "/storage/emulated/0/Android/data/com.nali.scene/"
	#define NALI_F_SAVE NALI_F_PACKAGE "save"
	#define NALI_F_READ_CACHE NALI_F_PACKAGE "c"
#else
	#define NALI_F_HOME "../assets/"
	#define NALI_F_SAVE "save/"
#endif

#define NALI_F_HOME_SOUND NALI_F_HOME "sound/"
#define NALI_F_HOME_SOUND_BGM NALI_F_HOME_SOUND "bgm.ogg"

// #define NALI_F_HOME_IMAGE NALI_F_HOME "image"

#define NALI_F_HOME_ASSET NALI_F_HOME "assets.bin"
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
