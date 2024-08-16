#!/bin/bash
basic_sh="./scripts/basic"  # 修正了变量赋值，去掉了等号两侧的空格
bash "$basic_sh/yuv.sh"
# 确保路径是正确的，并且脚本是可执行的
if [ -x "$basic_sh/yuv.sh" ]; then
  # 使用变量执行脚本
  bash "$basic_sh/yuv.sh"
else
  echo "Error: yuv.sh does not exist or is not executable at $basic_sh/yuv.sh"
fi