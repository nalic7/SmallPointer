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
$mainMod = SUPER

bind = $mainMod, f11, fullscreen, 0
bind = $mainMod, f, fullscreenstate, 2,

bind = $mainMod, Q, exec, foot
bind = $mainMod, C, killactive,
bind = $mainMod, M, exit,
bind = $mainMod, V, togglefloating,
bind = $mainMod, P, pseudo,
bind = $mainMod, J, togglesplit,

bind = $mainMod, left, movefocus, l
bind = $mainMod, right, movefocus, r
bind = $mainMod, up, movefocus, u
bind = $mainMod, down, movefocus, d

bind = $mainMod, 1, workspace, 1
bind = $mainMod, 2, workspace, 2
bind = $mainMod, 3, workspace, 3
bind = $mainMod, 4, workspace, 4
bind = $mainMod, 5, workspace, 5
bind = $mainMod, 6, workspace, 6
bind = $mainMod, 7, workspace, 7
bind = $mainMod, 8, workspace, 8
bind = $mainMod, 9, workspace, 9
bind = $mainMod, 0, workspace, 10

bind = $mainMod SHIFT, 1, movetoworkspace, 1
bind = $mainMod SHIFT, 2, movetoworkspace, 2
bind = $mainMod SHIFT, 3, movetoworkspace, 3
bind = $mainMod SHIFT, 4, movetoworkspace, 4
bind = $mainMod SHIFT, 5, movetoworkspace, 5
bind = $mainMod SHIFT, 6, movetoworkspace, 6
bind = $mainMod SHIFT, 7, movetoworkspace, 7
bind = $mainMod SHIFT, 8, movetoworkspace, 8
bind = $mainMod SHIFT, 9, movetoworkspace, 9
bind = $mainMod SHIFT, 0, movetoworkspace, 10

bind = $mainMod, S, togglespecialworkspace, magic
bind = $mainMod SHIFT, S, movetoworkspace, special:magic

bindm = $mainMod, mouse:272, movewindow
bindm = $mainMod, mouse:273, resizewindow
#WINDOWS AND WORKSPACES
windowrule = suppressevent maximize, class:.*
windowrule = nofocus,class:^$,title:^$,xwayland:1,floating:1,fullscreen:0,pinned:0
```
>Tinywl
```
tinywl -s foot > /dev/null 2>&1
```
>Package (System/Debug)
```
sys-devel/gcc-14.3.0
dev-debug/gdb-16.3
```
>Package (Code)
```
gui-apps/foot-1.19.0
app-editors/vim-9.1.0794
```
>~/.config/foot/foot.ini
```
[main]
font=Monospace:size=12
[colors]
background=000000
```
>~/.vimrc
```
set number
set list
set listchars=tab:>-,trail:·,space:␣
```
>Package/Debug (Android)
```
dev-util/android-sdk-build-tools-34
dev-util/android-tools-35.0.2
```
>Package (Portable)
```
blender-4.4.3
```
# [README](../README.md)
