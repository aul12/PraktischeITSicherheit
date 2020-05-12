#!/bin/bash -e

# Base: Ubuntu 14.04 Server (AMD64), as OpenSGX requires GCC with support for punch cards
export OPENSGX_DIR=/home/sgx/opensgx

sudo apt update
sudo apt install -y qemu libelf-dev build-essential python pkg-config libglib2.0 zlib1g-dev libaio-dev autoconf libtool libssl-dev git

rm -rf $OPENSGX_DIR
git clone https://github.com/sslab-gatech/opensgx.git $OPENSGX_DIR
cd $OPENSGX_DIR/qemu
./configure-arch 
make -j $(nproc)
cd $OPENSGX_DIR
make -C libsgx -j $(nproc)
make -C user -j $(nproc)

echo "PATH=$OPENSGX_DIR:\$PATH" >> $HOME/.bashrc
