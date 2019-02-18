#!/bin/bash

set -e
( source /etc/os-release ; if [[ ( "$NAME" != "Ubuntu" ) || ( "$VERSION_ID" != "18.04" ) ]]; then echo "Unsupported OS!"; exit 255; fi; )

sudo apt-get install -y libgmp-dev libfftw3-dev

(
    su vagrant <<'EOF'
    cd ~
    git clone https://github.com/tfhe/tfhe.git
    cd tfhe/
    git checkout -q v1.0.1
    git submodule update --init
    mkdir -p build
    cd build/
    cmake ../src -DENABLE_TESTS=on -DENABLE_FFTW=on -DCMAKE_BUILD_TYPE=optim -DCMAKE_INSTALL_PREFIX="/usr"
    make
EOF
    cd /home/vagrant/tfhe
    make install
)
