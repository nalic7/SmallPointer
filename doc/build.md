# Build
>Start Path
```bash
git clone https://github.com/spacecat393/SmallPointer
cd SmallPointer
```
>Wayland (Linux)
```bash
mkdir lib
cd lib
mkdir wayland
cd wayland
../SmallPointer/run/wayland
cd ../..
```
>FFMPEG (Android)
```bash
cd ..
git clone --branch release/7.1 https://github.com/FFmpeg/FFmpeg.git
cd FFmpeg
../SmallPointer/run/ffmpeg-android
cd ../SmallPointer
```
>cgltf (Header)
```bash
cd ..
git clone https://github.com/jkuhlmann/cgltf
cd SmallPointer
```
>Vulkan (Compile Shader)
```bash
run/vulkan
```
>Compile (Release)
```bash
cmake -DCMAKE_BUILD_TYPE=Release -B build-release -S .
cmake --build build-release -j$(nproc)
```
>Compile (Debug)
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build-debug -S .
cmake --build build-debug -j$(nproc)
```
>Debug
```bash
cd build-debug
gdb SmallPointer
```
