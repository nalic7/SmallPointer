# Minecraft Cleanroom
>Install/Run PrismLauncher
```bash
cd ..
mkdir prism
cd prism
wget https://github.com/PrismLauncher/PrismLauncher/releases/download/9.4/PrismLauncher-Linux-x86_64.AppImage
wget https://github.com/CleanroomMC/Cleanroom/releases/download/0.3.13-alpha/Cleanroom-MMC-instance-0.3.13-alpha.zip
chmod +x PrismLauncher-Linux-x86_64.AppImage
HOME=$(pwd) ./PrismLauncher-Linux-x86_64.AppImage
cd ../SmallPointer
```
>Java arguments
```
-agentpath:<HOME_PATH>/SmallPointer/build-release/libSmallPointer.so
```
>Log
```bash
vi ../prism/.local/share/PrismLauncher/instances/Cleanroom-MMC-instance-0.3.13-alpha/minecraft/save/log.dat
```
