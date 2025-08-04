# [Blend](source/blend)
# [Shader](source/shader)
# [Path](doc/path.md)
# [Gentoo Linux](doc/gentoo.md)
# README
>Extensions

Code-GCC [clangd](https://github.com/clangd/vscode-clangd)  
CMake [CMake Tools](https://github.com/microsoft/vscode-cmake-tools)  
Debug-GDB [CodeLLDB](https://github.com/vadimcn/codelldb)  
GLSL [Shader validator](https://github.com/antaalt/shader-validator)  
MD [Markdown Editor](https://github.com/zaaack/vscode-markdown-editor)
<!-- Vim [Vim](https://github.com/VSCodeVim/Vim) -->
>~/.config/VSCodium/User/settings.json
```json
{
	"editor.largeFileOptimizations": false,
	"editor.renderWhitespace": "all",
	"clangd.enableCodeCompletion": false,
	"editor.minimap.enabled": false,
	"cmake.debugConfig.type": "lldb",
	"editor.insertSpaces": false,
	"editor.tabSize": 4,
	"editor.detectIndentation": false,
	"[cmake]":
	{
		"editor.insertSpaces": true,
		"editor.tabSize": 2
	}
}
```
<!-- ```json
	// "vim.useSystemClipboard": true,
	// "editor.lineNumbers": "relative",
	// "vim.normalModeKeyBindingsNonRecursive":
	// [
	// 	{
	// 		"before": ["g", "r"],
	// 		"commands": ["editor.action.referenceSearch.trigger"]
	// 	}
	// ],
	// "workbench.activityBar.location": "top",
	// "window.customTitleBarVisibility": "windowed",
	// "editor.cursorSmoothCaretAnimation": "on",
	// "editor.smoothScrolling": true,
	// "workbench.list.smoothScrolling": true,
	// "terminal.integrated.smoothScrolling": true,
``` -->
>Compile Shader
```bash
#vulkan SPIR-V
cd asset

glslc ../source/shader/0.vert -o vert.spv
glslc ../source/shader/0.frag -o frag.spv
```
>Build Library
```bash
# /SmallPointer

#wayland (Linux build)
mkdir lib
cd lib
mkdir wayland
cd wayland
../SmallPointer/run/wayland

#ffmpeg (Android build)
cd ..
git clone --branch release/7.1 https://github.com/FFmpeg/FFmpeg.git
cd FFmpeg
../SmallPointer/run/ffmpeg-android

#cgltf (gltf to raw data)
cd ..
git clone https://github.com/jkuhlmann/cgltf
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
<!-- ### LWJGL64
>JVM arguments
	-Dorg.lwjgl.librarypath=/path
	-Dorg.lwjgl3.glfw.libname=/path
### NALIGL
### NALIAL -->