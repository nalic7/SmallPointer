cmake_minimum_required(VERSION 3.31)

#//.c System
set(S_NAME linux)
#set(S_NAME android)
#set(S_NAME mc)

#//.c skip this for release
set(TEST 1)
set(TEST_3D 1)

#//.c debug log
set(DEBUG 1)

#//.c gen asset/skip this for release
set(GEN 1)

#//.c runtime
set(CLIENT 1)
#set(SERVER 1)

#//.c vk debug layer
set(VK_DEBUG 1)

set(P_NAME SmallPointer)
project(${P_NAME} LANGUAGES C)

file(GLOB_RECURSE G_SOURCES src/file/*.c)
list(APPEND SOURCES ${G_SOURCES})

set(TLL m)
file(GLOB_RECURSE G_SOURCES src/math/*.c)
list(APPEND SOURCES ${G_SOURCES})

if(TEST)
  list(APPEND TCD C_NALI_TEST)
  if(TEST_3D)
    list(APPEND TCD C_NALI_TEST_3D)

    file(GLOB_RECURSE G_SOURCES src/test/3d/*.c)
    list(APPEND SOURCES ${G_SOURCES})
  endif()
endif()

list(APPEND SOURCES src/debug/debug.c)
if(DEBUG)
  list(APPEND TCD C_NALI_DEBUG)
endif()

if(GEN)
  list(APPEND TCD C_NALI_GEN)
  file(GLOB_RECURSE G_SOURCES src/gen/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND TID ../cgltf)
endif()

file(GLOB_RECURSE G_SOURCES src/loader/both/*.c)
list(APPEND SOURCES ${G_SOURCES})

file(GLOB_RECURSE G_SOURCES src/entity/both/*.c)
list(APPEND SOURCES ${G_SOURCES})

if(CLIENT)
  list(APPEND TCD C_NALI_CLIENT)

  file(GLOB_RECURSE G_SOURCES src/vk/*.c)
  list(APPEND SOURCES ${G_SOURCES})
  if (VK_DEBUG)
    list(APPEND TCD C_NALI_VK_DEBUG)
    list(APPEND SOURCES src/vk/debug/debug.c)
  endif()

  list(APPEND SOURCES src/surface/surface.c)

  file(GLOB_RECURSE G_SOURCES src/loader/client/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND SOURCES src/network/network_client.c)

  list(APPEND SOURCES src/ffmpeg/ffmpeg.c)
endif()

if(SERVER)
  list(APPEND TCD C_NALI_SERVER)

  file(GLOB_RECURSE G_SOURCES src/loader/server/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND SOURCES src/network/network_server.c)

  file(GLOB_RECURSE G_SOURCES src/entity/server/*.c)
  list(APPEND SOURCES ${G_SOURCES})
endif()

if(S_NAME STREQUAL "android")
  list(APPEND TCD C_NALI_S_ANDROID)

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
  add_library(${P_NAME} SHARED ${SOURCES})
else()
  if(CLIENT)
    list(APPEND TLL vulkan)

    #//.i ffmpeg
    list(APPEND TLL
      avcodec
      avformat
      avutil
      swresample
    )

    #//.i pipewire
    list(APPEND TLL pipewire-0.3)
    list(APPEND TID /usr/include/spa-0.2)
    list(APPEND TID /usr/include/pipewire-0.3)

    #//.i wayland / surface
    list(APPEND TLL
      wayland-client
      wayland-cursor
    )

    file(GLOB_RECURSE G_SOURCES lib/wayland/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    file(GLOB_RECURSE G_SOURCES src/surface/wayland/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    list(APPEND SOURCES src/surface/surface_main.c)

    list(APPEND TID lib/wayland)
  endif()
  if(S_NAME STREQUAL "mc")
    list(APPEND TCD C_NALI_S_MC)

    list(APPEND TID ${CMAKE_SOURCE_DIR}/../jdk-24.0.2/include)
    list(APPEND TID ${CMAKE_SOURCE_DIR}/../jdk-24.0.2/include/linux)

    add_library(${P_NAME} SHARED ${SOURCES})
  else()
    add_executable(${P_NAME} ${SOURCES})
  endif()
endif()

if(TID)
  target_include_directories(${P_NAME} PRIVATE ${TID})
endif()
target_link_libraries(${P_NAME} ${TLL})
target_compile_definitions(${P_NAME} PRIVATE ${TCD})

target_precompile_headers(${P_NAME} PRIVATE src/pch.h)
