<!--toc:start-->
- [**Small Render**](#small-render)
    - [JVM arguments](#jvm-arguments)
    - [Build](#build)
- [**Collada Parser**](#collada-parser)
    - [Edit Model](#edit-model)
    - [Export Collada](#export-collada)
<!--toc:end-->

# **Small Render**
### JVM arguments
	-Dorg.lwjgl.librarypath=/path
	-Dorg.lwjgl3.glfw.libname=/path
### Build
	Library
	1. Vulkan 1.3.290.0
	2. OpenAL-Soft 1.23.1
	3. Java jdk8u412-b08
	4. Wayland
	5. Qt6
	6. X11
	7. GL

# **Collada Parser**
### Edit Model
	Blender 4.3.0-alpha+main.8f996f178604-linux.x86_64-release

	Apply[Ctrl+A]->All Transforms
	One Material One Object.
	Object Name as Outliner.
	Add all Bones to Vertex Groups.
	Data->Vertex Group Specials->Sort by Bone Hierarchy
### Export Collada
	Arm
	[/] Export to SL/OpenSim
	Anim
	[/] All Keyed Curves
