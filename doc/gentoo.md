# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
USE="-policykit screencast drun libdrm drm kms abi_x86_32 abi_x86_64 dist-kernel -daemon elogind sound-server pipewire-alsa pipewire -pulseaudio -ofono-headset -flatpak dracut efistub grub X xwayland wayland -kde -gnome -systemd -systemd-boot -xfce -gpm -emacs -vlc vulkan vulkan-overlay osmesa opengl mpv zeroconf telephony bluetooth extra ffmpeg hwaccel openal opus vdpau vaapi cuda png jpeg jpeg2k ssh nvenc"

INPUT_DEVICES="wacom libinput"

# AMD_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="amdgpu radeon radeonsi nvidia d3d12 d3d11 d3d10 d3d9 d3d8"

# Intel_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="intel nvidia d3d12 d3d11 d3d10 d3d9 d3d8"
```
>Package
```
gui-wm/hyprland-0.46.2-r1
```
# [README](../README.md)