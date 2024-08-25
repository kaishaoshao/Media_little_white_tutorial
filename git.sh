#!/bin/bash

# 检查是否提供了提交信息
if [ -z "$1" ]; then
	echo "error: add commit message"
	echo "tip: $0 <message>"
	exit 1
fi


commit_message="$1"

# 拉取源代码同步更新
git pull
if [ $? -ne 0 ]; then
	echo "failed to pull the main"
	exit 1
fi


# 添加所有更改到暂存区
git add .
if [ $? -ne 0 ]; then
	echo "failed to add changes to the staging area"
	exit 1
fi


# 检查是否有未提交的更改
if ! git diff-index --quiet HEAD --; then
	echo "uncommitted chages detected.executing the submission ..."
	git commit -am "$commit_message"
	if [ $? -ne 0 ]; then
		echo "push fail,please check error message"
		exit 1
	fi
fi


# 推送到远程仓库
git push -u origin HEAD

# 检查是否git push成功
if [ $? -eq 0 ]; then
	echo "push succeeful: message - <$commit_message> "
else
	echo "push fail,please check error message"
	exit 1
fi
