# poe-v3
PoE solution based on the V3 protocol

# make libsai.so

```
cd ./sai_poe_library
make -B
```

# make sai-poe.deb

```
mkdir -p ./sai-poe/usr/lib/
cp ./sai_poe_library/board_info/rdac5xpoe.xml .
md5sum rdac5xpoe.xml > rdac5xpoe.md5
mv rdac5xpoe* ./sai-poe/usr/lib/
cp ./sai_poe_library/libsai.so ./sai-poe/usr/lib/
dpkg-deb --build sai-poe
```

# update deb package in sonic-buildimage

```
cp sai-poe.deb /<path>/<to>/sonic-buildimage/platform/marvell/sai/debs/poelibsai.deb
```
