# Collada Parser
<span style="font-size: large; ">

>Install
1. Blender
2. CMake / nvim / VSCode

	VSCode Extensions

		C/C++ Debug (gdb)
		clangd
		CMake
		CMake Tools
		CodeLLDB

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

# Small Render
<span style="font-size: large; ">

>JVM arguments

	-Dorg.lwjgl.librarypath=/path
	-Dorg.lwjgl3.glfw.libname=/path
>Library
1. Vulkan 1.3.290.0
2. OpenAL-Soft 1.23.1
3. Java jdk8u412-b08
4. Wayland
5. Qt6
6. X11
7. GL

</span>