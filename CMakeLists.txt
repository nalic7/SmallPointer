cmake_minimum_required(VERSION 3.10)

set(OS_NAME linux)
set(GEN 1)
set(CLIENT 1)
set(VK_DEBUG 1)
set(SCENE 1)
# set(COLLADA 1)
# set(LWJGL64 1)
# set(NALIGL 1)
# set(NALIAL 1)

if (SCENE)
  set(P_NAME scene)
elseif(COLLADA)
  set(P_NAME collada)
elseif(LWJGL64)
  set(P_NAME lwjgl64)
elseif(NALIGL)
  set(P_NAME NaliGL)
elseif(NALIAL)
  set(P_NAME NaliAL)
endif()

project(${P_NAME} VERSION 1.0.0 LANGUAGES C)

# ISO C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED On)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++21")

if(SCENE)

  set(FOO PCH_SCENE=1)
  set(SOURCES
    src/file/file.c
    src/math/m4x4/m4x4.c
    src/surface/surface.c
    src/file/file.c
    src/al/al.c
    src/scene/scene.c
    src/ffmpeg/ffmpeg.c
  )

  if (GEN)
    list(APPEND FOO NALI_GEN=1)
    list(APPEND SOURCES src/gen/gen.c)
  endif()
  if (CLIENT)
    if (VK_DEBUG)
      list(APPEND FOO NALI_VK_DEBUG=1)
      list(APPEND SOURCES src/vk/debug/debug.c)
    endif()

    file(GLOB_RECURSE G_SOURCES src/vk/release/*.c)
    list(APPEND SOURCES ${G_SOURCES})
  
    file(GLOB_RECURSE G_SOURCES lib/wayland/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    file(GLOB_RECURSE G_SOURCES src/math/*.c)
    list(APPEND SOURCES ${G_SOURCES})
  
    file(GLOB_RECURSE G_SOURCES src/surface/wayland/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    list(APPEND FOO NALI_CLIENT=1)
    list(APPEND SOURCES src/loader/client/client.c)
    # list(APPEND SOURCES src/network/linux/client/nw_client.c)
  else()
    # list(APPEND SOURCES src/loader/server/l_server.c)
    # list(APPEND SOURCES src/network/linux/server/nw_server.c)
  endif()

  add_executable(${P_NAME} ${SOURCES})

  target_include_directories(${P_NAME} PRIVATE
    lib/wayland
  )

  target_link_libraries(${P_NAME}
    m
    vulkan
    openal

    wayland-client
    wayland-cursor

    avcodec
    avformat
    avutil
  )

  target_compile_definitions(${P_NAME} PRIVATE ${FOO})

  # set_target_properties(${P_NAME} PROPERTIES
  #   CMAKE_INSTALL_RPATH "$ORIGIN/../lib"
  # )

elseif(COLLADA)

  add_executable(${P_NAME}
    src/math/math.c
    src/math/m4x4/m4x4.c
    src/collada/collada.c
    src/collada/graphic_reader/graphic_reader.c
    src/collada/file_reader/file_reader.c
    src/collada/file_writer/file_writer.c
  )

  target_link_libraries(${P_NAME}
    m
  )

  target_compile_definitions(${P_NAME} PRIVATE PCH_COLLADA=1)

elseif(LWJGL64)

  set(JAVA_HOME lib/jdk8u412-b08/)
  # set(JAVA_HOME "lib/jdk-21.0.4+7/")

  find_package(Qt6 REQUIRED COMPONENTS Widgets WaylandClient)
  find_package(X11 REQUIRED)

  add_library(${P_NAME} SHARED
    src/surface/surface.c
    src/al/al.c
    src/vk/vk.c
    src/vk/instance/instance.c
    src/vk/instance/debug/debug.c
    src/vk/instance/physical_device/physical_device.c
    src/vk/instance/physical_device/queue/queue.c
    src/vk/instance/device/device.c
    src/vk/surface/surface.c
    src/vk/swapchain/swapchain.c
    src/vk/fence/fence.c
    src/vk/semaphore/semaphore.c
    src/vk/commandbuffer/commandpool/commandpool.c
    src/vk/commandbuffer/commandbuffer.c
    src/vk/heap/imageview/image/image.c
    src/vk/heap/imageview/imageview.c
    src/vk/shadermodule/shadermodule.c
    src/lwjgl/lwjgl.c
    src/lwjgl/gl/11/GL11.c
    src/lwjgl/gl/GL13.c
    src/lwjgl/gl/GL14.c
    src/lwjgl/gl/GL15.c
    src/lwjgl/gl/GL20.c
    src/lwjgl/gl/GL30.c
    src/lwjgl/gl/GLContext.c
    src/lwjgl/linux/LinuxContextImplementation.c
    src/lwjgl/linux/LinuxDisplay.c
    src/lwjgl/linux/LinuxDisplayPeerInfo.c
    src/lwjgl/linux/LinuxEvent.c
    src/lwjgl/linux/LinuxKeyboard.c
    src/lwjgl/linux/LinuxMouse.c
    src/lwjgl/linux/LinuxPeerInfo.c
    src/lwjgl/al/AL.c
    src/lwjgl/al/AL10.c
    src/lwjgl/al/AL11.c
    src/lwjgl/al/ALC10.c
    src/lwjgl/al/ALC11.c
    src/lwjgl/al/EFX10.c
  )

  target_include_directories(${P_NAME} PRIVATE
    ${JAVA_HOME}include
    ${JAVA_HOME}include/${OS_NAME}
  )

  target_link_libraries(${P_NAME}
    vulkan
    openal
    wayland-client
  )

  target_compile_definitions(${P_NAME} PRIVATE PCH_LWJGL64=1)

elseif(NALIGL)

  set(JAVA_HOME lib/jdk8u412-b08/)

  add_library(${P_NAME} SHARED src/gl/nali/glnali.c)

  target_include_directories(${P_NAME} PRIVATE
    ${JAVA_HOME}include
    ${JAVA_HOME}include/${OS_NAME}
  )

  target_compile_definitions(${P_NAME} PRIVATE PCH_NALIGL=1)

elseif(NALIAL)

  set(JAVA_HOME lib/jdk8u412-b08/)

  add_library(${P_NAME} SHARED src/al/nali/alnali.c)

  target_include_directories(${P_NAME} PRIVATE
    ${JAVA_HOME}include
    ${JAVA_HOME}include/${OS_NAME}
    AL
  )

  target_link_libraries(${P_NAME}
    openal
  )

  target_compile_definitions(${P_NAME} PRIVATE PCH_NALIAL=1)

endif()

target_precompile_headers(${P_NAME} PRIVATE src/pch.h)
