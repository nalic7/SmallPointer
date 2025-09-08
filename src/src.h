#ifndef hSMPT
	#define hSMPT

	#ifdef SMPT_CM_ST_MC
		//#include <jni.h>
		#include <jvmti.h>
	#endif

	#include <unistd.h>
	#include <math.h>
	#include <stdint.h>
	#include <sys/stat.h>
//	#include <ctype.h>
	#include <dirent.h>
	#include <time.h>
	#include <threads.h>
	#include <string.h>

	#include "raw/raw.h"

	#ifdef SMPT_CM_VK
		#ifdef SMPT_CM_DRM
//			#include <linux/vt.h>
//			#include <sys/ioctl.h>

			#define VK_USE_PLATFORM_DISPLAY_KHR
		#endif

		#ifdef SMPT_CM_WL
			#define VK_USE_PLATFORM_WAYLAND_KHR
		#endif

		#ifdef SMPT_CM_ST_ANDROID
			#define VK_USE_PLATFORM_ANDROID_KHR
		#endif

		#include <vulkan/vulkan.h>

		#ifdef SMPT_CM_VK_DEBUG
			#include "render/vk/debug/debug.h"
		#endif

		#include "render/vk/vk.h"
		#include "render/vk/queue/device/physical_device/instance/instance.h"
		#include "render/vk/queue/device/physical_device/physical_device.h"
		#include "render/vk/queue/device/device.h"
		#include "render/vk/queue/queue.h"
		#include "render/vk/surface/surface.h"
		#include "render/vk/renderpass.h"
		#include "render/vk/framebuffer.h"
		#include "render/vk/swapchain/swapchain.h"
		#include "render/vk/fence.h"
		#include "render/vk/semaphore.h"
		#include "render/vk/command/pool/pool.h"
		#include "render/vk/command/buffer/buffer.h"
		#include "render/vk/buffer/buffer.h"
		#include "render/vk/imageview/image.h"
		#include "render/vk/imageview/imageview.h"
		#include "render/vk/sampler.h"

		#include "render/vk/write/write.h"
		#include "render/vk/write/descriptorset/descriptorset.h"
		#include "render/vk/write/descriptorset/layout/layout.h"
		#include "render/vk/write/descriptorset/pool/pool.h"

		#include "render/vk/pipeline/layout/layout.h"
		#include "render/vk/pipeline/color.h"
		#include "render/vk/pipeline/dynamic.h"
		#include "render/vk/pipeline/input.h"
		#include "render/vk/pipeline/multi.h"
		#include "render/vk/pipeline/rasterization.h"
		#include "render/vk/pipeline/shader/shader.h"
		#include "render/vk/pipeline/vertex.h"
		#include "render/vk/pipeline/viewport.h"
		#include "render/vk/pipeline/depth.h"
		#include "render/vk/pipeline/pipeline.h"

		#include "render/vk/command/draw/draw.h"
	#endif

	#if SMPT_CM_DRM || SMPT_CM_ASURFACE || SMPT_CM_WL || SMPT_CM_X11
		#include "surface/surface.h"
	#endif

	#ifdef SMPT_CM_ST_LINUX
		#include <stdio.h>
		#include <stdlib.h>
		#include <limits.h>

		#include <linux/input-event-codes.h>

		#include <termios.h>

		#ifdef SMPT_CM_PIPEWIRE
			#include <pipewire/pipewire.h>
			//! audio data to 3d audio
		#endif

		#ifdef SMPT_CM_DRM
			#include <signal.h>
		#endif

		#ifdef SMPT_CM_LIBINPUT
			#include <libinput.h>
			#include "libinput/libinput.h"
		#endif

		#ifdef SMPT_CM_WL
			#include <wayland-cursor.h>
			#include <xdg-shell.h>
			#include <pointer-constraints-unstable-v1.h>
			#include <relative-pointer-unstable-v1.h>

			#include "surface/wayland/client/client.h"
			#include "surface/wayland/client/registry/registry.h"
			#include "surface/wayland/client/seat/seat.h"
			#include "surface/wayland/client/seat/keyboard/keyboard.h"
			#include "surface/wayland/client/seat/pointer/pointer.h"
			#include "surface/wayland/client/xdg/surface/surface.h"
			#include "surface/wayland/client/xdg/toplevel/toplevel.h"
			#include "surface/wayland/client/xdg/wm/wm.h"
			#include "surface/wayland/client/zwp/pointer/pointer.h"
			#include "surface/wayland/client/zwp/locked/locked.h"
			#include "surface/wayland/client/zwp/relative/relative.h"
		#endif
	#endif

	#ifdef SMPT_CM_ST_ANDROID
		#ifdef SMPT_CM_ASURFACE
			#include <android/native_activity.h>
			#include <android/native_window.h>
			#include <android/configuration.h>
		#endif
		#ifdef SMPT_CM_AAUDIO
			//! audio android
//			#include <aaudio/AAudio.h>
//			#include <SLES/OpenSLES.h>
			//! audio data to 3d audio
		#endif
		#ifdef SMPT_CM_AINPUT
			//! ainput
		#endif
		#include "android/android.h"
	#endif

	#ifdef SMPT_CM_FFMPEG
		#include "libavformat/avformat.h"
		#include <libavcodec/avcodec.h>
		//#include <libavutil/avutil.h>

		#include <libavutil/imgutils.h>
		//#include <libavutil/avassert.h>

		//#include <libswscale/swscale.h>
		#include <libswresample/swresample.h>
		#include "ffmpeg/ffmpeg.h"
	#endif

	#if SMPT_CM_CLIENT || SMPT_CM_SERVER
		#include <fcntl.h>
//		#include <errno.h>
//		#include <arpa/inet.h>
//		#include <sys/socket.h>
		#include <netinet/in.h>
		//.c port
		#define SMPTuPORT 11111
	#endif

	#ifdef SMPT_CM_CLIENT
		#include "raw/client/keyframe/keyframe.h"
		#include "raw/client/model/model.h"
		#include "raw/client/client.h"
		#include "raw/client/clientu.h"
		#include "raw/client/clientm.h"

		#ifdef SMPT_CM_UDP
			#include "network/udp/client/client.h"
		#endif
	#endif

	#ifdef SMPT_CM_SERVER
		#include "raw/server/server.h"
		#include "raw/server/serveru.h"
		#include "raw/server/serverm.h"

		#ifdef SMPT_CM_UDP
			#include "network/udp/server/server.h"
		#endif
		//#include <stdint.h>
		//#include <sys/epoll.h>
	#endif

	#include "file/file.h"

	#include "math/math.h"
	#include "math/m4x4/m4x4.h"
	#include "math/v4/v4.h"

	#ifdef SMPT_CM_GEN
		#include "gen/model/model.h"
		#include "gen/keyframe/keyframe.h"
		#include "gen/gen.h"
	#endif

	#include "test/test.h"
	#include "debug/debug.h"
#endif
