# SETUP
<span style="font-size: large;">

>Linux / Android

1. VSCodium

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

		clangd -> c
		CMake Tools -> cmake
		CodeLLDB -> debug
2. Blender 3.x 4.x
3. dev-util/android-studio 2024.2.2.14
</span>

### Scene
<span style="font-size: large;">

>CMakeLists.txt

	#...
	set(GEN 1) // for first time
	set(CLIENT 1)
	set(SERVER 1)
	set(VK_DEBUG 1)

	set(SCENE 1)
	#...
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

### LWJGL64
<span style="font-size: large;">

>JVM arguments

	-Dorg.lwjgl.librarypath=/path
	-Dorg.lwjgl3.glfw.libname=/path

</span>

### NALIGL
### NALIAL
