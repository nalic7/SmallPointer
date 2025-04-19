# SETUP
<span style="font-size: large;">

>Linux / Android

1. app-editors/vscodium-1.99.12392

	settings.json
	```json
	{
		"editor.largeFileOptimizations": false,
		"editor.renderWhitespace": "all",
		"clangd.enableCodeCompletion": false,
		"editor.minimap.enabled": false,
		"cmake.debugConfig.type": "lldb"
	}
	```

	Extensions

		clangd / c
		CMake Tools / cmake
		CodeLLDB / debug
2. dev-util/android-studio-2024.3.1.14
3. blender 4.4.0
</span>

### Scene
<span style="font-size: large;">

>Compile Shader
```bash
#vulkan SPIR-V
glslc
```

>Build Library
```bash
# /SmallRender

#wayland (Linux only)
mkdir lib
cd lib
mkdir wayland
cd wayland

wayland-scanner client-header /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml xdg-shell-client-protocol.h

wayland-scanner private-code /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml xdg-shell-protocol.c

wayland-scanner client-header /usr/share/wayland-protocols/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml pointer-constraints-unstable-v1.h

wayland-scanner private-code /usr/share/wayland-protocols/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml pointer-constraints-unstable-v1.c

wayland-scanner client-header /usr/share/wayland-protocols/unstable/relative-pointer/relative-pointer-unstable-v1.xml relative-pointer-unstable-v1.h

wayland-scanner private-code /usr/share/wayland-protocols/unstable/relative-pointer/relative-pointer-unstable-v1.xml relative-pointer-unstable-v1.c

#openal-soft (Android only)
cd ..
git clone https://github.com/kcat/openal-soft
cd openal-soft/build

cmake .. -DANDROID_NDK=/.../Android/Sdk/ndk/29.0.13113456 -DCMAKE_TOOLCHAIN_FILE=/.../Android/Sdk/ndk/29.0.13113456/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_STL=c++_static -DANDROID_HOST_TAG=linux-x86_64 -DNDK_CPU_ARM64=ON -DALSOFT_REQUIRE_OPENSL=1

make

#ffmpeg-android-maker (Android only)
cd ..
git clone https://github.com/Javernaut/ffmpeg-android-maker
cd ffmpeg-android-maker

ANDROID_SDK_HOME=/.../Android/Sdk ANDROID_NDK_HOME=/.../Android/Sdk/ndk/29.0.13113456 sh ffmpeg-android-maker.sh

#cgltf (Gen only)
cd ..
git clone https://github.com/jkuhlmann/cgltf
```

>CMakeLists.txt

```c#
#select build for
set(OS_NAME linux)
#...

set(DEBUG 1)
#build asset
set(GEN 1)
set(CLIENT 1)
set(SERVER 1)
set(VK_DEBUG 1)

set(SCENE 1)
#...
```
>src/pch.h

```c
//package path
#ifdef NALI_OS_ANDROID
	#define NALI_HOME "/.../com.nali.scene/"
//...
```
</span>

### Collada Parser
<span style="font-size: large;">

>CMakeLists.txt

	#...
	set(COLLADA 1)
	#...

>Edit Model In Blender
1. Apply[Ctrl+A] -> All Transforms
2. One Material One Object
3. Object Name as Outliner
4. Add all Bones to Vertex Groups
5. Data -> Vertex Group Specials -> Sort by Bone Hierarchy
>Export Collada Setting

	Arm
	[/] Export to SL/OpenSim
	Anim
	[/] All Keyed Curves
<!-- Anim -->
<!-- 	Key Type [Curves] -->
<!-- 	Transform [Decomposed] -->
>Run
1. \>CMake: Debug / create ```C_I``` in ```build```
2. Put ```model.dae``` to ```C_I```
3. \>CMake: Debug
4. Get Raw Data in ```C_O``` without error

</span>

<!-- ### LWJGL64
<span style="font-size: large;">

>JVM arguments

	-Dorg.lwjgl.librarypath=/path
	-Dorg.lwjgl3.glfw.libname=/path

</span>

### NALIGL
### NALIAL -->
