# Minecraft Cleanroom
>Build
```bash
run/java-gen
run/config
run/config-mc
cmake -DCMAKE_BUILD_TYPE=Release -B build-release -S .
cmake --build build-release
```
>Install Cleanroom & MCP/Run PrismLauncher
```bash
run/mc-gen
run/mc-run
```
>Java arguments
```
-agentpath:<HOME_PATH>/SmallPointer/build-release/libSmallPointer.so
```
>Byte
```bash
unzip ../prism/.local/share/PrismLauncher/libraries/com/mojang/minecraft/1.12.2/minecraft-1.12.2-client.jar -d ../prism/.local/share/PrismLauncher/libraries/com/mojang/minecraft/1.12.2/src
../jdk-24.0.2/bin/javap -c -p ../prism/.local/share/PrismLauncher/libraries/com/mojang/minecraft/1.12.2/src/*.class
```
>Log
```bash
vi ../prism/.local/share/PrismLauncher/instances/Cleanroom-MMC-instance-0.3.13-alpha/minecraft/save/log.dat
```
