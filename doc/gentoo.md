# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
#OpenRC AMD64
USE="builtin server -elogind -fonts -policykit -pulseaudio sound-server pipewire-alsa pipewire ffmpeg extra drm X xwayland wayland vaapi bluetooth -gpm jpeg2k opus"

INPUT_DEVICES="libinput"

#AMD_igpu
VIDEO_CARDS="amdgpu radeonsi"

#Intel_igpu
VIDEO_CARDS="intel"

#NVIDIA_dgpu
VIDEO_CARDS="nvidia nouveau nvk zink"
```
>Config kbdrate
```bash
sudo kbdrate -r 30 -d 250
```
>Install Package (dwl blender)
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
ln -sfn /usr/src/linux-6.17.0 /usr/src/linux
make mrproper
make defconfig
make menuconfig
```
>Update Kernel
```bash
make mrproper
cp /usr/src/linux-6.16.*/.config /usr/src/linux-6.17.0
make oldconfig
```
>Compile/Reinstall Kernel/Modules
```bash
make
make modules_install
cp arch/x86/boot/bzImage /boot/vmlinuz-6.17.0
grub-mkconfig -o /boot/grub/grub.cfg
```
>Clean Kernel
```bash
rm -r /usr/src/linux-6.16.*
rm -r /lib/modules/6.16.*
rm /boot/vmlinuz-6.16.*
```
>~/.vimrc
```
set number relativenumber list listchars=tab:>-,trail:·,space:_ nowrap
highlight SpecialKey guifg=#ff0000 ctermfg=Red
highlight NonText guifg=#ff0000 ctermfg=Red
autocmd BufRead,BufNewFile CMakeLists.txt setlocal expandtab shiftwidth=2 softtabstop=2
```
