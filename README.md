# Scene
<span style="font-size: large; ">

>CMakeLists.txt

	#...
	set(VK_DEBUG 1)
	set(SCENE 1)
	#...
</span>

# Collada Parser
<span style="font-size: large; ">

>CMakeLists.txt

	#...
	set(COLLADA 1)
	#...
>Install
1. Blender
2. CMake / nvim / VSCode

	VSCode Extensions

		C/C++ Debug (gdb)
		clangd
		CMake Tools

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

# LWJGL64
<span style="font-size: large; ">

>JVM arguments

	-Dorg.lwjgl.librarypath=/path
	-Dorg.lwjgl3.glfw.libname=/path

</span>

# NALIGL
# NALIAL
