#!/bin/bash -e
export OPENSGX_DIR=/tmp/opensgx

function cleanup {
    echo "Cleanup..."
    rm -rf $OPENSGX_DIR
}
trap cleanup EXIT

sudo apt update
sudo apt install -y qemu libelf-dev build-essential python pkg-config libglib2.0 zlib1g-dev libaio-dev autoconf libtool libssl-dev

rm -rf $OPENSGX_DIR
git clone https://github.com/sslab-gatech/opensgx.git $OPENSGX_DIR
cd $OPENSGX_DIR/qemu
./configure-arch 
make -C $OPENSGX_DIR/qemu -j $(nproc)
make -C $OPENSGX_DIR/libsgx -j $(nproc)
make -C $OPENSGX_DIR/user -j $(nproc)
