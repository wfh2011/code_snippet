#!/bin/bash

set -e      # 遇到异常退出
#set -x      # 开启调试模式

# 目录参数：
# SCRIPT_DIR:                               当前脚本文件路径
# PROJ_SRC:                                 源码路径
# PROJ_ROOT:                                项目路径
# PROJ_BUILD:                               构建生成路径
# PROJ_BUILD_BIN_DIR:                       可执行文件目录
SCRIPT_DIR="$(cd "$(dirname "$0")"; pwd -P)"
PROJ_SRC="$(dirname $SCRIPT_DIR)"
PROJ_ROOT="$(dirname $PROJ_SRC)"
PROJ_BUILD=${PROJ_ROOT}/build
PROJ_BUILD_BIN_DIR=${PROJ_BUILD}/$(go env GOOS)_$(go env GOARCH)/bin

if [ -f $PROJ_BUILD ]; then
    echo "$PROJ_BUILD is file, please check it."
    exit 1
fi

rm -fr $PROJ_BUILD
if [ ! -d $PROJ_BUILD ]; then
    mkdir -p $PROJ_BUILD
fi

export GOROOT=$(go env GOROOT)
export GOPROXY=https://goproxy.io
export GOPATH=${PROJ_ROOT}
export GO111MODULE="off"


echo $PROJ_BUILD_BIN_DIR

go get gopkg.in/redis.v5