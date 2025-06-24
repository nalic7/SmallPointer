# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
#OpenRC AMD64
USE="-policykit drun drm kms dist-kernel -daemon elogind sound-server pipewire-alsa pipewire -pulseaudio -ofono-headset -flatpak dracut efistub grub X xwayland wayland -kde -gnome -systemd -systemd-boot -xfce -gpm -emacs -vlc vulkan vulkan-overlay osmesa opengl mpv zeroconf telephony bluetooth extra ffmpeg hwaccel openal opus vdpau vaapi cuda png jpeg jpeg2k ssh nvenc"

INPUT_DEVICES="wacom libinput"

#AMD_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="amdgpu radeon radeonsi nvidia"

#Intel_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="intel nvidia"
```
>Package
```
gui-wm/hyprland-0.46.2-r1
llvm-core/clang-20.1.7
app-editors/vscodium-1.100.33714
dev-util/android-studio-2024.3.2.14
```
>Package (Portable)
```
blender-4.4.3
```
# [README](../README.md)