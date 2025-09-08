# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
#OpenRC AMD64
USE="-fonts -policykit -pulseaudio sound-server pipewire-alsa pipewire ffmpeg extra drm X xwayland wayland vaapi bluetooth -gpm jpeg2k opus"

INPUT_DEVICES="libinput"

#AMD_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="amdgpu radeonsi nouveau nvk zink"

#Intel_cpu,igpu / NVIDIA_dgpu
VIDEO_CARDS="intel nvidia nouveau nvk zink"
```
>Install Package
```bash
run/gentoo
```
>Check Kernel
```bash
ls /usr/src
ls -l /usr/src/linux
ls /lib/modules
cd /usr/src/linux
```
>Set/Default Kernel
```bash
ln -sfn /usr/src/linux-6.16.5 /usr/src/linux
make mrproper
make defconfig
make menuconfig
```
>Update Kernel
```bash
make mrproper
cp /usr/src/linux-6.16.4/.config /usr/src/linux-6.16.5
make oldconfig
```
>Compile/Reinstall Kernel/Modules
```bash
make
make modules_install
cp arch/x86/boot/bzImage /boot/vmlinuz-6.16.5
grub-mkconfig -o /boot/grub/grub.cfg
emerge -a @module-rebuild
```
>Clean Kernel
```bash
rm -rf /usr/src/linux-6.16.4
rm -rf /lib/modules/6.16.4
rm /boot/vmlinuz-6.16.4
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
>~/.vimrc
```
set number relativenumber list listchars=tab:>-,trail:·,space:_ nowrap
highlight SpecialKey guifg=#ff0000 ctermfg=Red
highlight NonText guifg=#ff0000 ctermfg=Red
autocmd BufRead,BufNewFile CMakeLists.txt setlocal expandtab shiftwidth=2 softtabstop=2
```
>Install Blender
```bash
cd ..
wget https://mirror.freedif.org/blender/release/Blender4.5/blender-4.5.1-linux-x64.tar.xz
tar -xf blender-4.5.1-linux-x64.tar.xz
rm blender-4.5.1-linux-x64.tar.xz
cd SmallPointer
```
