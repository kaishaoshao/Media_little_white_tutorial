#!/bin/bash
src_basic="../../src/basic"
output_basic="../../output/basic"

echo "Current directory: $(pwd)"
if [ ! -f "$src_basic/pcm.cpp" ]; then
    echo "Source file does not exist: $src_basic/pcm.cpp"
    exit 1
fi

# Make sure the output directory exists
mkdir -p "$output_basic"

# Compile the source file
clang++  -g "$src_basic/pcm.cpp" -o "$output_basic/pcm"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable is at: $output_basic/pcm"
    ./"$output_basic/pcm"   
    echo "**********************************************"
    echo "run $output_basic/pcm successful"
    echo "**********************************************"
else
    echo "Compilation failed."
    exit 1
fi

