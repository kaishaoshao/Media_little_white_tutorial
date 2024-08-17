#!/bin/bash
src_basic="../../src/basic"
output_basic="../../output/basic"

echo "Current directory: $(pwd)"
if [ ! -f "$src_basic/yuv.cpp" ]; then
    echo "Source file does not exist: $src_basic/yuv.cpp"
    exit 1
fi

# Make sure the output directory exists
mkdir -p "$output_basic"

# Compile the source file
clang++ "$src_basic/yuv.cpp" -o "$output_basic/yuv"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable is at: $output_basic/yuv"
    ./"$output_basic/yuv"
    echo "run $output_basic/yuv successful"
else
    echo "Compilation failed."
    exit 1
fi

