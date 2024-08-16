#!/bin/bash
src_basic="../../src/basic"
output_basic="../../output/basic"
clang "$src_basic/yuv.cpp" -o "$output_basic"/yuv
"$output_basic"/yuv