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

# Copy libsai.so into the specified directory
cp libsai.so /local/store/sai-poe/poelibsai-debian/usr/lib/

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

