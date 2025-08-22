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

			#include "surface/android/android.h"
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
			#include "surface/wayland/client/xdg/wm_base/wm_base.h"
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

	#include "loader/both/both.h"
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

		#include "vk/vk.h"
		#include "vk/queue/device/physical_device/instance/instance.h"
		#ifdef C_NALI_VK_DEBUG
			#include "vk/debug/debug.h"
		#endif
		#include "vk/queue/device/physical_device/physical_device.h"
		#include "vk/queue/device/device.h"
		#include "vk/queue/queue.h"
		#include "vk/surface/surface.h"
		#include "vk/renderpass.h"
		#include "vk/framebuffer.h"
		#include "vk/swapchain/swapchain.h"
		#include "vk/fence.h"
		#include "vk/semaphore/semaphore.h"
		#include "vk/commandbuffer/commandpool/commandpool.h"
		#include "vk/commandbuffer/commandbuffer.h"
		#include "vk/buffer/buffer.h"
		#include "vk/imageview/image.h"
		#include "vk/imageview/imageview.h"
		#include "vk/shadermodule/shadermodule.h"
		#include "vk/sampler.h"

		#include "vk/descriptorset/descriptorset.h"
		#include "vk/descriptorset/layout/layout.h"
		#include "vk/descriptorset/pool/pool.h"

		#include "vk/graphicspipeline/pipelinelayout/pipelinelayout.h"
		#include "vk/graphicspipeline/colorblendstatecreateinfo.h"
		#include "vk/graphicspipeline/dynamicstatecreateinfo.h"
		#include "vk/graphicspipeline/inputassemblystatecreateinfo.h"
		#include "vk/graphicspipeline/multisamplestatecreateinfo.h"
		#include "vk/graphicspipeline/rasterizationstatecreateinfo.h"
		#include "vk/graphicspipeline/shaderstagecreateinfo/shaderstagecreateinfo.h"
		#include "vk/graphicspipeline/vertexinputstatecreateinfo.h"
		#include "vk/graphicspipeline/viewportstatecreateinfo.h"
		#include "vk/graphicspipeline/depthstencilstatecreateinfo.h"
		#include "vk/graphicspipeline/graphicspipeline.h"

		#include "vk/cmd/cmd.h"
		#include "vk/cmd/image/image.h"
		#include "vk/cmd/draw/draw.h"

		#include "loader/client/client_a.h"
		#include "loader/client/client_u.h"
		#include "loader/client/client_m.h"
		#include "loader/client/keyframe/keyframe.h"
		#include "loader/client/shader/shader.h"
		#include "loader/client/pose/pose.h"
		#include "loader/client/client.h"
		#include "network/network_client.h"
	#endif

	#ifdef C_NALI_SERVER
		#include <math.h>
		// #include <stdint.h>
		// #include <sys/epoll.h>

		#include "loader/server/server.h"
		#include "loader/server/server_a.h"
		#include "loader/server/server_u.h"
		#include "loader/server/server_m.h"
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
