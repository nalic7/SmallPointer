# Minecraft Cleanroom
>Build
```bash
cd ..
wget https://download.java.net/java/GA/jdk24.0.2/fdc5d0102fe0414db21410ad5834341f/12/GPL/openjdk-24.0.2_linux-x64_bin.tar.gz
tar -xf openjdk-24.0.2_linux-x64_bin.tar.gz
rm openjdk-24.0.2_linux-x64_bin.tar.gz
cd SmallPointer
run/config
run/config-mc
cmake -DCMAKE_BUILD_TYPE=Release -B build-release -S .
cmake --build build-release
```
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
