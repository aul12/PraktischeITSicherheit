#!/bin/bash -e

# Base: Ubuntu 14.04 Server (AMD64), as OpenSGX requires GCC with support for punch cards
export OPENSGX_DIR=$HOME/opensgx

sudo apt update
sudo apt install -y qemu libelf-dev build-essential python pkg-config libglib2.0 zlib1g-dev libaio-dev autoconf libtool libssl-dev git figlet

rm -rf $OPENSGX_DIR
git clone https://github.com/sslab-gatech/opensgx.git $OPENSGX_DIR
cd $OPENSGX_DIR
git checkout 6cc1fe6 # See #40
cd $OPENSGX_DIR/qemu
./configure-arch 
make -j $(nproc)
cd $OPENSGX_DIR
make -C libsgx -j $(nproc)
make -C user -j $(nproc)

echo "export OPENSGX_DIR=$OPENSGX_DIR" >> $HOME/.bashrc

cp -r $(dirname $0)/Template/* $HOME

figlet "PLEASE LOGOUT AND LOGIN OR RUN 'source ~./bashrc'"
