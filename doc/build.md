# Build
>Start Path
```bash
git clone https://github.com/spacecat393/SmallPointer
cd SmallPointer
chmod +x run/*
```
>Wayland (Linux)
```bash
run/wayland
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
cd ..
```
>Android Tool
```bash
run/android-tool
```
>Compile/Install (Release Android)
```bash
run/android-apk
```
>Run/Log (Android)
```bash
adb shell am start -n com.nali.smallpointer/android.app.NativeActivity
adb shell cat storage/emulated/0/Android/data/com.nali.smallpointer/save/log.dat
```
# [README](../README.md)
