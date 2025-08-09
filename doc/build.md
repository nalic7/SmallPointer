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
JAVA_HOME=$(pwd)/jdk-24.0.2 cmdline-tools/bin/sdkmanager "platforms;android-32" --sdk_root=$(pwd)
cd SmallPointer
```
>Compile (Release Android)
```bash
cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=../android-ndk-r27d/build/cmake/android.toolchain.cmake \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-32 \
  -B build-android-release \
  -S .
cmake --build build-android-release
../android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/bin/llvm-strip build-android-release/libSmallPointer.so
aapt2 link \
  -o build-android-release/smallpointer.apk \
  -I ../platforms/android-32/android.jar \
  --manifest AndroidManifest.xml \
  -A asset
mkdir -p apk/lib/arm64-v8a
cp build-android-release/libSmallPointer.so apk/lib/arm64-v8a
cp ../FFmpeg/android/arm64/lib/libavcodec.so apk/lib/arm64-v8a
cp ../FFmpeg/android/arm64/lib/libavformat.so apk/lib/arm64-v8a
cp ../FFmpeg/android/arm64/lib/libavutil.so apk/lib/arm64-v8a
cp ../FFmpeg/android/arm64/lib/libswresample.so apk/lib/arm64-v8a
cd apk
zip -r ../build-android-release/smallpointer.apk lib
cd ..
../jdk-24.0.2/bin/keytool -genkeypair \
  -alias androiddebugkey \
  -keypass android \
  -keystore build-android-release/.keystore \
  -storepass android \
  -dname "CN=Android Debug,O=Android,C=US" \
  -keyalg RSA \
  -keysize 2048 \
  -validity 10000
zipalign -p -f 4 build-android-release/smallpointer.apk build-android-release/smallpointer-aligned.apk
PATH=$(pwd)/../jdk-24.0.2/bin:$PATH apksigner sign --ks build-android-release/.keystore \
  --ks-pass pass:android \
  --key-pass pass:android \
  --ks-key-alias androiddebugkey \
  build-android-release/smallpointer-aligned.apk
```
>Install (Android)
```bash
adb shell pm uninstall --user 0 com.nali.smallpointer
adb install build-android-release/smallpointer-aligned.apk
```
>Run/Log (Android)
```bash
adb shell am start -n com.nali.smallpointer/android.app.NativeActivity
adb shell cat storage/emulated/0/Android/data/com.nali.smallpointer/save/log.dat
```
# [README](../README.md)
