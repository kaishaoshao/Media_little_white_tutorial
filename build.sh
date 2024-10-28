#!/bin/bash
output_basic="./output/basic/"
output_basic_pic="./output/basic/pic/"
basic_sh="./scripts/basic"  

# 检查是否传入了 --clean 参数
if [ "$1" == "--clean" ]; then
  # 如果是 --clean 参数，删除 output_basic_pic 目录下的所有文件
  rm "$output_basic_pic"* -f
  rm "$output_basic"* -f
  echo "Cleaned up the $output_basic and $output_basic_pic directory."
  exit 0
elif [ "$1" == "--help" ];then
  echo "This script compiles the program and processes the data"
  echo "No parameters is compilation"
  echo "--help    : Get Help"
  echo "--chean   : Clear compilation produces data"
  echo "--basic"  : compiler the baisc
  echo "--look    : Viewing the generated data"
  echo "--player  : Start yuvplayer"
  echo "--git     : Update and push code "
  echo "             |- build.sh --git <message>"
  exit 0
elif [ "$1" == "--look" ];then 
  ls ./output/basic/pic/
  exit 0
elif [ "$1" == "--player" ];then 
  ./tools/yuvplayer.exe &
  exit 0
elif [ "$1" == "--git" ];then
  if [ $# -lt 2 ];then 
    echo "No push messages"
    exit 1
  else
    bash ./scripts/git.sh $2
    exit 0
  fi
elif [ "$1" == "--basic" ];then
    cd  "$basic_sh"
    if [ "$2" == "yuv" ];then
        bash "yuv.sh"   
    elif [ "$2" == "pcm" ];then
        bash "pcm.sh"   
    fi
else
  cd  "$basic_sh"
  # 确保路径正确,脚本是可执行
  if [ -x "yuv.sh" ]; then
    # 执行脚本
    bash "yuv.sh"
  else
    echo "Error: yuv.sh does not exist or is not executable at $basic_sh/yuv.sh"
  fi
  exit 0
fi

