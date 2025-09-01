cmake_minimum_required(VERSION 3.31)

#//.i system
set(ST linux)
#set(ST android)
#set(ST win11)
#set(ST mc)

#//.i surface
set(DRM 1)
#set(ANDROID 1)
#set(WL 1)
#set(X11 1)

#//.i run
#set(GEN 1)
set(CLIENT 1)
#set(SERVER 1)

#//.i media reader
set(FFMPEG 1)

#//.i network protocol
set(UDP 1)
#set(TCP 1)

#//.i audio
set(PIPEWIRE 1)
#set(AAUDIO 1)
#set(OPENAL 1)

#//.i render
set(VK 1)
  set(VK_DEBUG 1)
#set(GL 1)

set(TEST 1)
set(TEST_3D 1)

set(DEBUG 1)

set(PN SmallPointer)
project(${PN} LANGUAGES C)

file(GLOB_RECURSE G_SOURCES src/file/*.c)
list(APPEND SOURCES ${G_SOURCES})

set(TLL m)
file(GLOB_RECURSE G_SOURCES src/math/*.c)
list(APPEND SOURCES ${G_SOURCES})

if(TEST)
  list(APPEND TCD _CM_TEST)
  if(TEST_3D)
    list(APPEND TCD _CM_TEST_3D)

    file(GLOB_RECURSE G_SOURCES src/test/3d/*.c)
    list(APPEND SOURCES ${G_SOURCES})
  endif()
endif()

list(APPEND SOURCES src/debug/debug.c)
if(DEBUG)
  list(APPEND TCD _CM_DEBUG)
endif()

if(GEN)
  list(APPEND TCD _CM_GEN)

  file(GLOB_RECURSE G_SOURCES src/gen/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND TID ../cgltf)
endif()

file(GLOB_RECURSE G_SOURCES src/raw/both/*.c)
list(APPEND SOURCES ${G_SOURCES})

file(GLOB_RECURSE G_SOURCES src/entity/both/*.c)
list(APPEND SOURCES ${G_SOURCES})

if(CLIENT)
  list(APPEND TCD _CM_CLIENT)

  if(VK)
    list(APPEND TCD _CM_VK)

    file(GLOB_RECURSE G_SOURCES src/render/vk/*.c)
    list(APPEND SOURCES ${G_SOURCES})
    if (VK_DEBUG)
      list(APPEND TCD _CM_VK_DEBUG)
      list(APPEND SOURCES src/render/vk/debug/debug.c)
    endif()
  endif()

  list(APPEND SOURCES src/surface/surface.c)

  file(GLOB_RECURSE G_SOURCES src/raw/client/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND SOURCES src/network/network_client.c)

#  list(APPEND SOURCES src/ffmpeg/ffmpeg.c)
endif()

if(SERVER)
  list(APPEND TCD _CM_SERVER)

  file(GLOB_RECURSE G_SOURCES src/raw/server/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND SOURCES src/network/network_server.c)

  file(GLOB_RECURSE G_SOURCES src/entity/server/*.c)
  list(APPEND SOURCES ${G_SOURCES})
endif()

if(ST STREQUAL "android")
  list(APPEND TCD _CM_ST_ANDROID)

  #//! audio android
  list(APPEND TLL
    log
    android
    #OpenSLES
  )

  if(CLIENT)
    list(APPEND TLL ${CMAKE_SOURCE_DIR}/../android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/24/libvulkan.so)

    #//.i ffmpeg
    list(APPEND TID ../FFmpeg/android/arm64/include)
    list(APPEND TLL
      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libavcodec.so
      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libavformat.so
      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libavutil.so

      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libswresample.so
    )

    #//.i surface
    file(GLOB_RECURSE G_SOURCES src/surface/android/*.c)
    list(APPEND SOURCES ${G_SOURCES})
  endif()
  add_library(${PN} SHARED ${SOURCES})
elseif(ST STREQUAL "linux")
  if(DRM)
    list(APPEND TCD _CM_DRM)

    #//.i libinput
    file(GLOB_RECURSE G_SOURCES src/libinput/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    list(APPEND TLL
      input
      udev
    )
  endif()

  if(CLIENT)
    list(APPEND TCD _CM_ST_LINUX)

    list(APPEND TLL vulkan)

#    #//.i ffmpeg
#    list(APPEND TLL
#      avcodec
#      avformat
#      avutil
#      swresample
#    )

    #//.i pipewire
    list(APPEND TLL pipewire-0.3)
    list(APPEND TID /usr/include/spa-0.2)
    list(APPEND TID /usr/include/pipewire-0.3)

    #//.i wayland / surface
    if(WL)
      list(APPEND TCD _CM_WL)

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
    list(APPEND SOURCES src/src.c)

    add_executable(${PN} ${SOURCES})
  endif()
elseif(ST STREQUAL "mc")
  list(APPEND TCD _CM_ST_MC)

  list(APPEND TID ${CMAKE_SOURCE_DIR}/../jdk-24.0.2/include)
  list(APPEND TID ${CMAKE_SOURCE_DIR}/../jdk-24.0.2/include/linux)

  file(GLOB_RECURSE G_SOURCES src/mc/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  add_library(${PN} SHARED ${SOURCES})
endif()

if(TID)
  target_include_directories(${PN} PRIVATE ${TID})
endif()
target_link_libraries(${PN} ${TLL})
target_compile_definitions(${PN} PRIVATE ${TCD})

target_precompile_headers(${PN} PRIVATE src/src.h)
