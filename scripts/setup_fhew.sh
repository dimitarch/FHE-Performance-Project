#!/bin/bash

set -e
( source /etc/os-release ; if [[ ( "$NAME" != "Ubuntu" ) || ( "$VERSION_ID" != "18.04" ) ]]; then echo "Unsupported OS!"; exit 255; fi; )

sudo apt-get install -y libfftw3-dev

(
    su vagrant <<'EOF'
    cd ~
    git clone https://github.com/lducas/FHEW.git
    cd FHEW/
    make PREFIX='/usr'
EOF
    cd /home/vagrant/FHEW
    make PREFIX='/usr' install
)
