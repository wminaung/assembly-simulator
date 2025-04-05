#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Compile
g++ -g src/*.cpp -o build/main.exe

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Running the program..."
    ./build/main.exe
else
    echo "Compilation failed!"
fi
