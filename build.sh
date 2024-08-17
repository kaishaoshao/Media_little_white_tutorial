#!/bin/bash
output_basic_pic="./output/basic/pic/"
basic_sh="./scripts/basic"  

# 检查是否传入了 --clean 参数
if [ "$1" == "--clean" ]; then
  # 如果是 --clean 参数，删除 output_basic_pic 目录下的所有文件
  rm "$output_basic_pic"* -f
  echo "Cleaned up the $output_basic_pic directory."
else
  echo "No clean operation requested."
fi

cd  "$basic_sh"
# 确保路径正确,脚本是可执行
if [ -x "yuv.sh" ]; then
  # 执行脚本
  bash "yuv.sh"
else
  echo "Error: yuv.sh does not exist or is not executable at $basic_sh/yuv.sh"
fi

