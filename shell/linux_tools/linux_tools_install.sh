#!/bin/bash

# 指定下载路径
PREFIX=/home/rpm
if [ -d ${PREFIX} ]; then
    mkdir -p ${PREFIX}
fi

# yumdownloader依赖yum-utils
yum clean all
yum -y install yum-utils

# 下载常见的包
echo "Start download rpm, dir: ${PREFIX}"
yumdownloader --resolve --destdir=${PREFIX}/yum-utils yum-utils
yumdownloader --resolve --destdir=${PREFIX}/lrzsz lrzsz
yumdownloader --resolve --destdir=${PREFIX}/wget wget
yumdownloader --resolve --destdir=${PREFIX}/net-tools.x86_64 net-tools.x86_64
yumdownloader --resolve --destdir=${PREFIX}/git git
yumdownloader --resolve --destdir=${PREFIX}/svn svn
yumdownloader --resolve --destdir=${PREFIX}/sysstat sysstat
yumdownloader --resolve --destdir=${PREFIX}/gcc gcc
yumdownloader --resolve --destdir=${PREFIX}/gcc-c++ gcc-c++
yumdownloader --resolve --destdir=${PREFIX}/gdb gdb
yumdownloader --resolve --destdir=${PREFIX}/tcpdump tcpdump
yumdownloader --resolve --destdir=${PREFIX}/epel-release epel-release
yumdownloader --resolve --destdir=${PREFIX}/python-pip python-pip
yumdownloader --resolve --destdir=${PREFIX}/samba samba
yumdownloader --resolve --destdir=${PREFIX}/samba-common samba-common
yumdownloader --resolve --destdir=${PREFIX}/samba-client samba-client
yumdownloader --resolve --destdir=${PREFIX}/openssl openssl
yumdownloader --resolve --destdir=${PREFIX}/openssl-devel openssl-devel
yumdownloader --resolve --destdir=${PREFIX}/pcre pcre
yumdownloader --resolve --destdir=${PREFIX}/pcre-devel pcre-devel
yumdownloader --resolve --destdir=${PREFIX}/nc nc
yumdownloader --resolve --destdir=${PREFIX}/lsof lsof
yumdownloader --resolve --destdir=${PREFIX}/autoconf autoconf
yumdownloader --resolve --destdir=${PREFIX}/automake automake
yumdownloader --resolve --destdir=${PREFIX}/tree tree
yumdownloader --resolve --destdir=${PREFIX}/valgrind valgrind
yumdownloader --resolve --destdir=${PREFIX}/cmake cmake
yumdownloader --resolve --destdir=${PREFIX}/python-devel python-devel
yumdownloader --resolve --destdir=${PREFIX}/docker docker
yumdownloader --resolve --destdir=${PREFIX}/vim vim
yumdownloader --resolve --destdir=${PREFIX}/kvm kvm
yumdownloader --resolve --destdir=${PREFIX}/graphviz graphviz
yumdownloader --resolve --destdir=${PREFIX}/java java
echo "Succeed to download rpm, dir: ${PREFIX}"

# 安装常见的包
echo "Start to install rpm"
yum -y install yum-utils
yum -y install net-tools.x86_64
yum -y install git
yum -y install svn
yum -y install sysstat
yum -y install gcc
yum -y install gcc-c++
yum -y install gdb
yum -y install tcpdump

yum -y install samba
yum -y install samba-common
yum -y install samba-client
yum -y install openssl
yum -y install openssl-devel
yum -y install pcre
yum -y install pcre-devel
yum -y install nc
yum -y install lsof
yum -y install autoconf
yum -y install automake
yum -y install tree
yum -y install valgrind
yum -y install docker
yum -y install vim
yum -y install kvm
yum -y install graphviz
yum -y install java
yum -y install java-1.8.0-openjdk* # not download
echo "End to install rpm"

# 安装常见的python包
yum -y install epel-release
yum -y install python-devel
yum -y install python-pip
pip install --upgrade pip
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
python -m pip install --upgrade setuptools
pip install glances
pip install prettytable