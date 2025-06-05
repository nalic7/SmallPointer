cmake_minimum_required(VERSION 3.31)

set(S_NAME linux)
# set(S_NAME android)

set(DEBUG 1)
# set(GEN 1)
set(CLIENT 1)
set(SERVER 1)
set(VK_DEBUG 1)

set(SCENE 1)
# set(COLLADA 1)

# set(LWJGL64 1)
# set(NALIGL 1)
# set(NALIAL 1)

if (SCENE)
  set(P_NAME scene)
# elseif(COLLADA)
#   set(P_NAME collada)
# elseif(LWJGL64)
#   set(P_NAME lwjgl64)
# elseif(NALIGL)
#   set(P_NAME NaliGL)
# elseif(NALIAL)
#   set(P_NAME NaliAL)
endif()

project(${P_NAME} VERSION 1.0.0 LANGUAGES C)

# ISO C11
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_STANDARD_REQUIRED On)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

if(SCENE)
  set(TCD PCH_SCENE)
  set(SOURCES
    src/scene/scene.c
  )

  file(GLOB_RECURSE G_SOURCES src/file/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  set(TLL m)
  file(GLOB_RECURSE G_SOURCES src/math/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  if(DEBUG)
    list(APPEND TCD NALI_DEBUG)
    # list(APPEND SOURCES src/debug/debug.c)
  endif()

  if(GEN)
    list(APPEND TCD NALI_GEN)
    file(GLOB_RECURSE G_SOURCES src/gen/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    list(APPEND TID ../cgltf)
  endif()

  file(GLOB_RECURSE G_SOURCES src/loader/both/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND SOURCES src/network/linux/both/both.c)

  if(CLIENT)
    list(APPEND TCD NALI_CLIENT)

    list(APPEND TLL vulkan)
    file(GLOB_RECURSE G_SOURCES src/vk/release/*.c)
    list(APPEND SOURCES ${G_SOURCES})
    if (VK_DEBUG)
      list(APPEND TCD NALI_VK_DEBUG)
      list(APPEND SOURCES src/vk/debug/debug.c)
    endif()

    list(APPEND SOURCES src/surface/surface.c)

    file(GLOB_RECURSE G_SOURCES src/loader/client/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    list(APPEND SOURCES src/network/linux/client/client.c)

    list(APPEND SOURCES src/ffmpeg/ffmpeg.c)
    list(APPEND SOURCES src/al/al.c)
  endif()

  if(SERVER)
    list(APPEND TCD NALI_SERVER)

    list(APPEND SOURCES src/loader/server/server.c)
    list(APPEND SOURCES src/network/linux/server/server.c)
  endif()

  if(S_NAME STREQUAL "android")
    list(APPEND TCD NALI_S_ANDROID)

    list(APPEND TLL
      log
      android
      # OpenSLES
    )

    if(CLIENT)
      list(APPEND TID ../ffmpeg-android-maker/build/ffmpeg/arm64-v8a/include)
      list(APPEND TLL
        ${CMAKE_SOURCE_DIR}/../ffmpeg-android-maker/build/ffmpeg/arm64-v8a/lib/libavcodec.so
        ${CMAKE_SOURCE_DIR}/../ffmpeg-android-maker/build/ffmpeg/arm64-v8a/lib/libavformat.so
        ${CMAKE_SOURCE_DIR}/../ffmpeg-android-maker/build/ffmpeg/arm64-v8a/lib/libavutil.so

        ${CMAKE_SOURCE_DIR}/../ffmpeg-android-maker/build/ffmpeg/arm64-v8a/lib/libswresample.so
      )

      list(APPEND TID ../openal-soft/include)
      list(APPEND TLL ${CMAKE_SOURCE_DIR}/../openal-soft/build/libopenal.so)

      file(GLOB_RECURSE G_SOURCES src/surface/android/*.c)
      list(APPEND SOURCES ${G_SOURCES})
    endif()

    add_library(${P_NAME} SHARED ${SOURCES})
  else()
    if(CLIENT)
      list(APPEND TLL
        avcodec
        avformat
        avutil
        swresample
      )

      list(APPEND TLL openal)

      list(APPEND TLL
        wayland-client
        wayland-cursor
      )

      file(GLOB_RECURSE G_SOURCES lib/wayland/*.c)
      list(APPEND SOURCES ${G_SOURCES})

      file(GLOB_RECURSE G_SOURCES src/surface/wayland/*.c)
      list(APPEND SOURCES ${G_SOURCES})

      list(APPEND TID lib/wayland)
    endif()

    add_executable(${P_NAME} ${SOURCES})
  endif()

  if(TID)
    target_include_directories(${P_NAME} PRIVATE ${TID})
  endif()
  target_link_libraries(${P_NAME} ${TLL})
  target_compile_definitions(${P_NAME} PRIVATE ${TCD})
# elseif(COLLADA)
#   add_executable(${P_NAME}
#     src/math/math.c
#     src/math/m4x4/m4x4.c
#     src/collada/collada.c
#     src/collada/graphic_reader/graphic_reader.c
#     src/collada/file_reader/file_reader.c
#     src/collada/file_writer/file_writer.c
#   )

#   target_link_libraries(${P_NAME}
#     m
#   )

#   target_compile_definitions(${P_NAME} PRIVATE PCH_COLLADA)
# elseif(LWJGL64)
#   set(JAVA_HOME lib/jdk8u412-b08/)

#   add_library(${P_NAME} SHARED
#     src/surface/surface.c
#     src/al/al.c
#     src/vk/vk.c
#     src/vk/instance/instance.c
#     src/vk/instance/debug/debug.c
#     src/vk/instance/physical_device/physical_device.c
#     src/vk/instance/physical_device/queue/queue.c
#     src/vk/instance/device/device.c
#     src/vk/surface/surface.c
#     src/vk/swapchain/swapchain.c
#     src/vk/fence/fence.c
#     src/vk/semaphore/semaphore.c
#     src/vk/commandbuffer/commandpool/commandpool.c
#     src/vk/commandbuffer/commandbuffer.c
#     src/vk/heap/imageview/image/image.c
#     src/vk/heap/imageview/imageview.c
#     src/vk/shadermodule/shadermodule.c
#     src/lwjgl/lwjgl.c
#     src/lwjgl/gl/11/GL11.c
#     src/lwjgl/gl/GL13.c
#     src/lwjgl/gl/GL14.c
#     src/lwjgl/gl/GL15.c
#     src/lwjgl/gl/GL20.c
#     src/lwjgl/gl/GL30.c
#     src/lwjgl/gl/GLContext.c
#     src/lwjgl/linux/LinuxContextImplementation.c
#     src/lwjgl/linux/LinuxDisplay.c
#     src/lwjgl/linux/LinuxDisplayPeerInfo.c
#     src/lwjgl/linux/LinuxEvent.c
#     src/lwjgl/linux/LinuxKeyboard.c
#     src/lwjgl/linux/LinuxMouse.c
#     src/lwjgl/linux/LinuxPeerInfo.c
#     src/lwjgl/al/AL.c
#     src/lwjgl/al/AL10.c
#     src/lwjgl/al/AL11.c
#     src/lwjgl/al/ALC10.c
#     src/lwjgl/al/ALC11.c
#     src/lwjgl/al/EFX10.c
#   )

#   target_include_directories(${P_NAME} PRIVATE
#     ${JAVA_HOME}include
#     ${JAVA_HOME}include/${S_NAME}
#   )

#   target_link_libraries(${P_NAME}
#     vulkan
#     openal
#     wayland-client
#   )

#   target_compile_definitions(${P_NAME} PRIVATE PCH_LWJGL64)
# elseif(NALIGL)
#   set(JAVA_HOME lib/jdk8u412-b08/)

#   add_library(${P_NAME} SHARED src/gl/nali/glnali.c)

#   target_include_directories(${P_NAME} PRIVATE
#     ${JAVA_HOME}include
#     ${JAVA_HOME}include/${S_NAME}
#   )

#   target_compile_definitions(${P_NAME} PRIVATE PCH_NALIGL)
# elseif(NALIAL)
#   set(JAVA_HOME lib/jdk8u412-b08/)

#   add_library(${P_NAME} SHARED src/al/nali/alnali.c)

#   target_include_directories(${P_NAME} PRIVATE
#     ${JAVA_HOME}include
#     ${JAVA_HOME}include/${S_NAME}
#     AL
#   )

#   target_link_libraries(${P_NAME}
#     openal
#   )

#   target_compile_definitions(${P_NAME} PRIVATE PCH_NALIAL)
endif()

target_precompile_headers(${P_NAME} PRIVATE src/pch.h)