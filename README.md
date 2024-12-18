# poe-v3
PoE solution based on the V3 protocol

## v3 protocol
PoE API and protocol between the Host software and the Power management (PM) running on the service-CPU (SCPU). The data transfer mechanism is IPC, which allows both the host and SCPU to communicate via shared memory.

## make poelibsai.deb
```sh
cd sai-poe-implementation
./build_and_package.sh
```

## step by step
```sh
cd ./sai-poe-implementation
make
cd ..
cp ./sai-poe-implementation/board_info/rdac5xpoe.xml .
md5sum rdac5xpoe.xml > rdac5xpoe.md5
mv rdac5xpoe* ./poelibsai-debian/usr/lib/
cp ./sai-poe-implementation/libsai.so ./poelibsai-debian/usr/lib/
dpkg-deb --build poelibsai-debian poelibsai.deb
```