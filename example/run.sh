#!/bin/bash

echo "Building the project..."
make -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

echo "Build completed successfully. Cleaning up..."
rm -f *.o ../src/*.o

./example
