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
>Android Tool
```bash
cd ..
wget https://dl.google.com/android/repository/android-ndk-r27d-linux.zip
unzip android-ndk-r27d-linux.zip
rm android-ndk-r27d-linux.zip
wget https://dl.google.com/android/repository/commandlinetools-linux-13114758_latest.zip
unzip commandlinetools-linux-13114758_latest.zip
rm commandlinetools-linux-13114758_latest.zip
wget wget https://download.java.net/java/GA/jdk24.0.2/fdc5d0102fe0414db21410ad5834341f/12/GPL/openjdk-24.0.2_linux-x64_bin.tar.gz
tar -xf openjdk-24.0.2_linux-x64_bin.tar.gz
rm openjdk-24.0.2_linux-x64_bin.tar.gz
JAVA_HOME=$(pwd)/jdk-24.0.2 cmdline-tools/bin/sdkmanager "platforms;android-31" --sdk_root=$(pwd)
cd SmallPointer
```
>Compile (Debug Android)
```bash
cmake \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_TOOLCHAIN_FILE=../android-ndk-r27d/build/cmake/android.toolchain.cmake \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-21 \
  -B build-android-debug \
  -S .
cmake --build build-android-debug
```
>Compile (Release Android)
```bash
cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=../android-ndk-r27d/build/cmake/android.toolchain.cmake \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-21 \
  -B build-android-release \
  -S .
cmake --build build-android-release
../android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/bin/llvm-strip build-android-release/libSmallPointer.so
```
>Compile apk (Debug Android)
```bash
aapt2 link \
  -o build-android-debug/smallpointer.apk \
  -I ../platforms/android-31/android.jar \
  --manifest AndroidManifest.xml \
  -A asset \
  --min-sdk-version 24 \
  --target-sdk-version 31 \
  --shared-lib \
  --no-static-lib-packages
mkdir -p apk/lib/arm64-v8a
cp build-android-debug/libSmallPointer.so apk/lib/arm64-v8a
cd apk
zip -r ../build-android-debug/smallpointer.apk lib
cd ..
```
>Debug (Android)
```bash
adb install -r build-android-debug/smallpointer.apk
../android-ndk-r27d/ndk-gdb --launch=com.nali.smallpointer
```
# [README](../README.md)
