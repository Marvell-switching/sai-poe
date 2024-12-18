#!/bin/bash

# Remove the build directory
rm -rf build/

# Run the make command with the specified makefile
make -f Makefile

# Check if the build was successful before proceeding
if [ $? -ne 0 ]; then
    echo "Make failed, aborting."
    exit 1
fi

# Copy libsai.so into the debian directory
cp libsai.so /local/store/sai-poe/poelibsai-debian/usr/lib/

#Create md5 for board specific files
cd  ./board_info
md5sum rdac5xpoe.xml > rdac5xpoe.md5

# Copy board specific files into the debian directory
cp rdac5xpoe* ./../../poelibsai-debian/usr/bin/

# Check if the copy was successful before proceeding
if [ $? -ne 0 ]; then
    echo "Copying libsai.so failed, aborting."
    exit 1
fi

# Change directory to /local/store/sai-poe
cd /local/store/sai-poe

# Check if changing the directory was successful
if [ $? -ne 0 ]; then
    echo "Changing directory to /local/store/sai-poe failed, aborting."
    exit 1
fi

# Build the Debian package
dpkg-deb --build poelibsai-debian poelibsai.deb

# Check if the package building was successful
if [ $? -ne 0 ]; then
    echo "Building Debian package failed, aborting."
    exit 1
fi

echo "Script executed successfully."

