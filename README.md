# [Blend](source/blend)
# [Shader](source/shader)
# [Path](doc/path.md)
# [Gentoo Linux](doc/gentoo.md)
# README
>Build
```bash
# /SmallPointer

#wayland (Linux)
mkdir lib
cd lib
mkdir wayland
cd wayland
../SmallPointer/run/wayland

#ffmpeg (Android)
cd ..
git clone --branch release/7.1 https://github.com/FFmpeg/FFmpeg.git
cd FFmpeg
../SmallPointer/run/ffmpeg-android

#cgltf (Header)
cd ..
git clone https://github.com/jkuhlmann/cgltf

#vulkan (Compile shader)
run/vulkan
```
>[CMakeLists.txt](CMakeLists.txt)

>[vk.h](src/vk/release/vk/vk.h)

>[both.h](src/loader/both/both.h)

>[client.h](src/loader/client/client.h)

>[server.h](src/loader/server/server.h)

>[network_client.h](src/network/network_client.h)

>[network_server.h](src/network/network_server.h)

>[network_server.c](src/network/network_server.c)

>[file.h](src/file/file.h)

>[debug.h](src/debug/debug.h)
