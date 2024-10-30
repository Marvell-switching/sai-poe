# poe-v3
PoE solution based on the V3 protocol

# make libsai.so

```
cd ./sai_poe_library
make -B
```

# make sai-poe.deb

```
cp ./sai_poe_library/libsai.so ./sai-poe/usr/lib/
dpkg-deb --build sai-poe
```
