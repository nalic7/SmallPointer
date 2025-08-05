# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
#OpenRC AMD64
USE="-llvm -fonts -policykit efistub drun dist-kernel elogind dracut grub -pulseaudio sound-server pipewire-alsa dri drm kms pipewire ffmpeg extra X xwayland wayland osmesa vaapi nvdec nvenc vulkan vulkan-overlay telephony bluetooth gpm jpeg2k opus"

INPUT_DEVICES="wacom libinput"

#AMD_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="amdgpu radeonsi nvidia"

#Intel_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="intel nvidia"
```
>Package (Wayland)
```
#low
gui-wm/tinywl-0.18.1

#full
gui-wm/hyprland-0.49.0
```
>Package (System/Debug)
```
sys-devel/gcc-14.3.0
dev-debug/gdb-16.3
```
>Package (Code)
```
app-editors/vim-9.1.0794
dev-util/android-studio-2025.1.2.11
```
>Package (Portable)
```
blender-4.4.3
```
# [README](../README.md)
