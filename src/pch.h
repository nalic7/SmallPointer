#ifndef NALI_PCH_H
#define NALI_PCH_H

// #include <stdint.h>
#include <sys/stat.h>
// #include <ctype.h>
#include <dirent.h>

#include <time.h>
#include <threads.h>

#include <string.h>

#ifdef C_NALI_S_ANDROID
	#include <jni.h>
	#include <android/log.h>
//		#include <android/looper.h>

	#ifdef C_NALI_CLIENT
		#define VK_USE_PLATFORM_ANDROID_KHR
		#include <vulkan/vulkan.h>

		#include <android/native_activity.h>
		#include <android/native_window.h>
//			#include <aaudio/AAudio.h>

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

		// #include <wayland-client.h>
		#include <wayland-cursor.h>
		#include <xdg-shell.h>
		#include <pointer-constraints-unstable-v1.h>
		#include <relative-pointer-unstable-v1.h>
		// #include <wayland-server.h>
		// #include <wayland-util.h>

		#define VK_USE_PLATFORM_WAYLAND_KHR
		#include <vulkan/vulkan.h>

		//pipewire
		#include <pipewire/pipewire.h>

		#include "surface/wayland/client/client.h"
		#include "surface/wayland/client/register/register.h"
		#include "surface/wayland/client/seat/seat.h"
		#include "surface/wayland/client/seat/keyboard/keyboard.h"
		#include "surface/wayland/client/seat/pointer/pointer.h"
		#include "surface/wayland/client/xdg/surface/surface.h"
		#include "surface/wayland/client/xdg/toplevel/toplevel.h"
		#include "surface/wayland/client/xdg/wm_base/wm_base.h"
		#include "surface/wayland/client/zwp/zwp.h"
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

	//switch to pipewire linux
	//switch to AAudio android
	// #include <AL/al.h>
	// #include <AL/alc.h>

	// #include "al/al.h"

	#include "vk/release/vk/vk.h"
	#include "vk/release/queue/device/physical_device/instance/instance.h"
	#ifdef C_NALI_VK_DEBUG
		#include "vk/debug/debug.h"
	#endif
	#include "vk/release/queue/device/physical_device/physical_device.h"
	#include "vk/release/queue/device/device.h"
	#include "vk/release/queue/queue.h"
	#include "vk/release/surface/surface.h"
	#include "vk/release/renderpass.h"
	#include "vk/release/framebuffer.h"
	#include "vk/release/swapchain/swapchain.h"
	#include "vk/release/fence.h"
	#include "vk/release/semaphore/semaphore.h"
	#include "vk/release/commandbuffer/commandpool/commandpool.h"
	#include "vk/release/commandbuffer/commandbuffer.h"
	#include "vk/release/buffer/buffer.h"
	#include "vk/release/imageview/image.h"
	#include "vk/release/imageview/imageview.h"
	#include "vk/release/shadermodule/shadermodule.h"
	#include "vk/release/sampler.h"

	#include "vk/release/descriptorset/descriptorset.h"
	#include "vk/release/descriptorset/layout/layout.h"
	#include "vk/release/descriptorset/pool/pool.h"

	#include "vk/release/graphicspipeline/pipelinelayout/pipelinelayout.h"
	#include "vk/release/graphicspipeline/colorblendstatecreateinfo.h"
	#include "vk/release/graphicspipeline/dynamicstatecreateinfo.h"
	#include "vk/release/graphicspipeline/inputassemblystatecreateinfo.h"
	#include "vk/release/graphicspipeline/multisamplestatecreateinfo.h"
	#include "vk/release/graphicspipeline/rasterizationstatecreateinfo.h"
	#include "vk/release/graphicspipeline/shaderstagecreateinfo/shaderstagecreateinfo.h"
	#include "vk/release/graphicspipeline/vertexinputstatecreateinfo.h"
	#include "vk/release/graphicspipeline/viewportstatecreateinfo.h"
	#include "vk/release/graphicspipeline/depthstencilstatecreateinfo.h"
	#include "vk/release/graphicspipeline/graphicspipeline.h"

	#include "vk/release/cmd/cmd.h"
	#include "vk/release/cmd/image/image.h"
	#include "vk/release/cmd/draw/draw.h"

	#include "loader/client/client_a.h"
	#include "loader/client/client_u.h"
	#include "loader/client/client_m.h"
	#include "loader/client/keyframe/keyframe.h"
	#include "loader/client/pose/pose.h"
	#include "loader/client/shader/shader.h"
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
// // #ifdef PCH_LWJGL64

// // 	// #include <stdio.h>
// // 	// #include <dlfcn.h>
// // 	// #include <stdint.h>
// // 	#include <stdlib.h>
// // 	#include <jni.h>
// // 	#include <threads.h>
// // 	#include <string.h>
// // 	// #include <math.h>

// // 	#include <png.h>

// // 	#include <wayland-client.h>
// // 	#include <wayland-xdg-shell-client-protocol.h>

// // 	#include <GL/gl.h>
// // 	#include <GL/glx.h>
// // 	#include <X11/Xlib.h>

// // 	#include "lwjgl/gl/11/GL11.h"

// // 	#include <al.h>
// // 	#include <alc.h>

// // 	#include <vulkan/vulkan.h>
// // 	#include <vulkan/vulkan_wayland.h>

// // 	#include "al/al.h"

// // 	#include "lwjgl/lwjgl.h"
// // 	#include "surface/surface.h"
// // 	#include "vk/vk.h"
// // 	#include "vk/instance/instance.h"
// // 	#include "vk/instance/debug/debug.h"
// // 	#include "vk/instance/physical_device/physical_device.h"
// // 	#include "vk/instance/physical_device/queue/queue.h"
// // 	#include "vk/surface/surface.h"
// // 	#include "vk/instance/device/device.h"
// // 	#include "vk/swapchain/swapchain.h"
// // 	#include "vk/fence/fence.h"
// // 	#include "vk/semaphore/semaphore.h"
// // 	#include "vk/commandbuffer/commandpool/commandpool.h"
// // 	#include "vk/commandbuffer/commandbuffer.h"
// // 	#include "vk/heap/imageview/image/image.h"
// // 	#include "vk/heap/imageview/imageview.h"
// // 	#include "vk/shadermodule/shadermodule.h"

// // 	#include <sys/stat.h>
// // 	#include <dirent.h>
// // 	// #include <ctype.h>

// // #endif
// // #ifdef PCH_NALIGL

// // 	// #include <stdio.h>
// // 	// #include <stdlib.h>

// // 	#define NALI_LWJGL2
// // 	#define NALI_X11
// // 	// #define NALI_EGL

// // 	// #define NALI_LWJGL3

// // 	#include <jni.h>

// // 	#ifdef NALI_LWJGL3
// // 		#include <GL/gl.h>
// // 		#define tlsGetFunction(index) (uintptr_t)((void**)(*__env)->reserved3)[index]
// // 		typedef void (APIENTRY* glGenVertexArraysPROC) (jint, uintptr_t);
// // 	#endif

// // 	#ifdef NALI_EGL
// // 		#include <EGL/egl.h>
// // 		#define GETPROCADDRESS(proc) eglGetProcAddress((const GLubyte*)proc)
// // 		#define NALI_LWJGL2
// // 	#endif

// // 	#ifdef NALI_X11
// // 		#include <GL/glx.h>
// // 		#define GETPROCADDRESS(proc) glXGetProcAddress((const GLubyte*)proc)
// // 		#define NALI_LWJGL2
// // 	#endif

// // #endif
// // #ifdef PCH_NALIAL

// // 	#include <stdio.h>
// // 	#include <stdlib.h>
// // 	#include <stdint.h>

// // 	#include <jni.h>

// // 	#include <al.h>
// // 	#include <alc.h>

// // #endif

#include "debug/debug.h"

#endif