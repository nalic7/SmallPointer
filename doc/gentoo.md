# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
#OpenRC AMD64
USE="-llvm -fonts -policykit efistub drun dist-kernel elogind dracut grub -pulseaudio sound-server pipewire-alsa dri drm pipewire ffmpeg extra X xwayland wayland osmesa vaapi nvdec nvenc vulkan vulkan-overlay telephony bluetooth gpm jpeg2k opus"

INPUT_DEVICES="wacom libinput"

#AMD_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="amdgpu radeonsi nvidia"

#Intel_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="intel nvidia"
```
>Package (Wayland)
```
gui-wm/hyprland-0.49.0
```
>Hyprland
```
env = XCURSOR_THEME,Adwaita
#LOOK AND FEEL
general {
    gaps_in = 5
    gaps_out = 20

    border_size = 2

    col.active_border = rgba(85858585)
    col.inactive_border = rgba(00000000)

    resize_on_border = false

    allow_tearing = false

    layout = dwindle
}

decoration:blur:enabled = false

decoration {
    active_opacity = 1.0
    inactive_opacity = 0.5
}

animations {
    enabled = no
}

dwindle {
    pseudotile = true
    preserve_split = true
}

master {
    new_status = master
}

misc {
    background_color = rgba(00000000)
    force_default_wallpaper = 0
    disable_hyprland_logo = true
}
#INPUT
input {
    kb_layout = us
    kb_variant =
    kb_model =
    kb_options =
    kb_rules =

    follow_mouse = 1

    sensitivity = 0

    numlock_by_default = true
    touchpad {
        natural_scroll = false
        disable_while_typing = false
    }
}
#KEYBINDINGS
SUPER = SUPER

bind = SUPER, f11, fullscreen, 0
bind = SUPER, f, fullscreenstate, 2,

bind = SUPER, Q, exec, kitty
bind = SUPER, C, killactive,
bind = SUPER, M, exit,
bind = SUPER, V, togglefloating,
bind = SUPER, P, pseudo,
bind = SUPER, J, togglesplit,

bind = SUPER, left, movefocus, l
bind = SUPER, right, movefocus, r
bind = SUPER, up, movefocus, u
bind = SUPER, down, movefocus, d

bind = SUPER, 1, workspace, 1
bind = SUPER, 2, workspace, 2
bind = SUPER, 3, workspace, 3
bind = SUPER, 4, workspace, 4
bind = SUPER, 5, workspace, 5
bind = SUPER, 6, workspace, 6
bind = SUPER, 7, workspace, 7
bind = SUPER, 8, workspace, 8
bind = SUPER, 9, workspace, 9
bind = SUPER, 0, workspace, 10

bind = SUPER SHIFT, 1, movetoworkspace, 1
bind = SUPER SHIFT, 2, movetoworkspace, 2
bind = SUPER SHIFT, 3, movetoworkspace, 3
bind = SUPER SHIFT, 4, movetoworkspace, 4
bind = SUPER SHIFT, 5, movetoworkspace, 5
bind = SUPER SHIFT, 6, movetoworkspace, 6
bind = SUPER SHIFT, 7, movetoworkspace, 7
bind = SUPER SHIFT, 8, movetoworkspace, 8
bind = SUPER SHIFT, 9, movetoworkspace, 9
bind = SUPER SHIFT, 0, movetoworkspace, 10

bind = SUPER, S, togglespecialworkspace, magic
bind = SUPER SHIFT, S, movetoworkspace, special:magic

bindm = SUPER, mouse:272, movewindow
bindm = SUPER, mouse:273, resizewindow
#WINDOWS AND WORKSPACES
windowrule = suppressevent maximize, class:.*
windowrule = nofocus,class:^$,title:^$,xwayland:1,floating:1,fullscreen:0,pinned:0
```
>Package (System/Debug)
```
sys-devel/gcc-14.3.0
dev-debug/gdb-16.3
```
>Package (Code)
```
x11-terms/kitty-0.42.2-r1
app-editors/vim-9.1.0794
```
>~/.vimrc
```
set number
set list
set listchars=tab:>-,trail:·,space:␣
autocmd BufRead,BufNewFile CMakeLists.txt setlocal expandtab shiftwidth=2 softtabstop=2
```
>Package/Debug (Android)
```
dev-util/android-sdk-build-tools-34
app-arch/zip-3.0-r7
app-arch/unzip-6.0_p29
dev-util/android-tools-35.0.2
```
>Install Blender
```bash
cd ..
wget https://mirror.freedif.org/blender/release/Blender4.5/blender-4.5.1-linux-x64.tar.xz
tar -xf blender-4.5.1-linux-x64.tar.xz
rm blender-4.5.1-linux-x64.tar.xz
cd SmallPointer
```
# [README](../README.md)
