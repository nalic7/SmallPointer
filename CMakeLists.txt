cmake_minimum_required(VERSION 3.10)

set(OS_NAME linux)
# set(GLTF 1)
set(COLLADA 1)
# set(LWJGL64 1)
# set(NALIGL 1)

if(GLTF)
  set(P_NAME gltf)
elseif(COLLADA)
  set(P_NAME collada)
elseif(LWJGL64)
  set(P_NAME lwjgl64)
elseif(NALIGL)
  set(P_NAME NaliGL)
endif()

project(${P_NAME} VERSION 1.0.0 LANGUAGES C)

# ISO C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED On)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++21")

if(GLTF)

  add_executable(${P_NAME}
    src/gltf/gltf.c
  )

  target_include_directories(${P_NAME} PRIVATE
    ../cgltf
  )

  target_compile_definitions(${P_NAME} PRIVATE PCH_GLTF=1)

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
  set(VULKAN_SDK lib/vulkan-1.3.290.0/x86_64/)

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
    ${VULKAN_SDK}include
    /usr/include/qt6/QtWaylandClient/6.7.3/QtWaylandClient/private
    ../openal-soft/include/AL
    # ${WAYLAND_CLIENT_INCLUDE_DIR}
    # ${OPENGL_INCLUDE_DIRS}
  )

  link_directories(${VULKAN_SDK}lib)

  target_link_libraries(${P_NAME}
    vulkan
    ${WAYLAND_CLIENT_LIBRARY}
    Qt6::Widgets
    Qt6::WaylandClient
    /home/nali/Documents/GitHub/openal-soft/build/libopenal.so
    # ${OPENGL_LIBRARIES}
    # ${X11_LIBRARIES}
    # png
  )

  target_compile_definitions(${P_NAME} PRIVATE PCH_LWJGL64=1)

elseif(NALIGL)

  set(JAVA_HOME lib/jdk8u412-b08/)

  add_library(${P_NAME} SHARED src/glnali.c)

  target_include_directories(${P_NAME} PRIVATE
    ${JAVA_HOME}include
    ${JAVA_HOME}include/${OS_NAME}
  )

  target_compile_definitions(${P_NAME} PRIVATE PCH_NALIGL=1)

endif()

target_precompile_headers(${P_NAME} PRIVATE src/pch.h)
