#ifndef NALI_PCH_H
#define NALI_PCH_H
	#ifdef C_NALI_S_MC
		#include <jvmti.h>
	#endif

	// #include <stdint.h>
	#include <sys/stat.h>
	// #include <ctype.h>
	#include <dirent.h>

	#include <time.h>
	#include <threads.h>

	#include <string.h>

	#ifdef C_NALI_S_ANDROID
		//#include <jni.h>
		//#include <jvmti.h>

		#ifdef C_NALI_CLIENT
			#define VK_USE_PLATFORM_ANDROID_KHR
			#include <vulkan/vulkan.h>

			#include <android/native_activity.h>
			#include <android/native_window.h>
			//! audio android
			#include <aaudio/AAudio.h>

			#include <SLES/OpenSLES.h>

			#include "android/android.h"
			#include <android/configuration.h>
		#endif
	#else
		#include <stdio.h>
		#include <stdlib.h>

		#ifdef C_NALI_CLIENT
			// #include <math.h>
			#include <limits.h>

			#include <linux/input.h>

			#include <wayland-cursor.h>
			#include <xdg-shell.h>
			#include <pointer-constraints-unstable-v1.h>
			#include <relative-pointer-unstable-v1.h>

			#define VK_USE_PLATFORM_WAYLAND_KHR
			#include <vulkan/vulkan.h>

			#include <pipewire/pipewire.h>

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

	//s0-ffmpeg
	#include "libavformat/avformat.h"
	#include <libavcodec/avcodec.h>
	// // #include <libavutil/avutil.h>

	#include <libavutil/imgutils.h>
	// #include <libavutil/avassert.h>

	// #include <libswscale/swscale.h>
	#include <libswresample/swresample.h>
	#include "ffmpeg/ffmpeg.h"
	//e0-ffmpeg

	#include "raw/both/both.h"
	#include "entity/both/pomi0/pomi0.h"
	#include "entity/both/pomi1/pomi1.h"
	#include "entity/both/pomi2/pomi2.h"

	#if C_NALI_CLIENT || C_NALI_SERVER
		#include <errno.h>
		#include <unistd.h>
		// #include <arpa/inet.h>
		#include <fcntl.h>
		#include <netinet/in.h> 
		// #include <sys/socket.h>
		#define NALI_SC_PORT 11111
	#endif

	#ifdef C_NALI_CLIENT
		#include "surface/surface.h"

		//! audio data to 3d audio

		#include "render/vk/vk.h"
		#include "render/vk/queue/device/physical_device/instance/instance.h"
		#ifdef C__VK_DEBUG
			#include "render/vk/debug/debug.h"
		#endif
		#include "render/vk/queue/device/physical_device/physical_device.h"
		#include "render/vk/queue/device/device.h"
		#include "render/vk/queue/queue.h"
		#include "render/vk/surface/surface.h"
		#include "render/vk/renderpass.h"
		#include "render/vk/framebuffer.h"
		#include "render/vk/swapchain/swapchain.h"
		#include "render/vk/fence.h"
		#include "render/vk/semaphore/semaphore.h"
		#include "render/vk/commandbuffer/commandpool/commandpool.h"
		#include "render/vk/commandbuffer/commandbuffer.h"
		#include "render/vk/buffer/buffer.h"
		#include "render/vk/imageview/image.h"
		#include "render/vk/imageview/imageview.h"
		#include "render/vk/shadermodule/shadermodule.h"
		#include "render/vk/sampler.h"

		#include "render/vk/descriptorset/descriptorset.h"
		#include "render/vk/descriptorset/layout/layout.h"
		#include "render/vk/descriptorset/pool/pool.h"

		#include "render/vk/graphicspipeline/pipelinelayout/pipelinelayout.h"
		#include "render/vk/graphicspipeline/colorblendstatecreateinfo.h"
		#include "render/vk/graphicspipeline/dynamicstatecreateinfo.h"
		#include "render/vk/graphicspipeline/inputassemblystatecreateinfo.h"
		#include "render/vk/graphicspipeline/multisamplestatecreateinfo.h"
		#include "render/vk/graphicspipeline/rasterizationstatecreateinfo.h"
		#include "render/vk/graphicspipeline/shaderstagecreateinfo/shaderstagecreateinfo.h"
		#include "render/vk/graphicspipeline/vertexinputstatecreateinfo.h"
		#include "render/vk/graphicspipeline/viewportstatecreateinfo.h"
		#include "render/vk/graphicspipeline/depthstencilstatecreateinfo.h"
		#include "render/vk/graphicspipeline/graphicspipeline.h"

		#include "render/vk/cmd/cmd.h"
		#include "render/vk/cmd/image/image.h"
		#include "render/vk/cmd/draw/draw.h"

		#include "raw/client/clienta.h"
		#include "raw/client/clientu.h"
		#include "raw/client/clientm.h"
		#include "raw/client/keyframe/keyframe.h"
		#include "raw/client/shader/shader.h"
		#include "raw/client/pose/pose.h"
		#include "raw/client/client.h"
		#include "network/network_client.h"
	#endif

	#ifdef C_NALI_SERVER
		#include <math.h>
		// #include <stdint.h>
		// #include <sys/epoll.h>

		#include "raw/server/server.h"
		#include "raw/server/servera.h"
		#include "raw/server/serveru.h"
		#include "raw/server/serverm.h"
		#include "network/network_server.h"

		#include "entity/server/pomi0/pomi0.h"
	#endif

	#include "file/file.h"

	#include "math/math.h"
	#include "math/m4x4/m4x4.h"
	#include "math/v4/v4.h"
	// #include "math/str/str.h"

	#ifdef C_NALI_GEN
		#include "gen/model/model.h"
		#include "gen/keyframe/keyframe.h"
		#include "gen/gen.h"
	#endif

	#include "debug/debug.h"
	#ifdef C_NALI_TEST
		#include "test/test.h"

		#ifdef C_NALI_TEST_3D
			#include "test/3d/3d.h"
		#endif
	#endif
#endif
