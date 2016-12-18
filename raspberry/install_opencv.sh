#!/bin/bash
    mkdir release
    cd release
    cmake -D CMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local ..
    make
    sudo make install
    echo 
    ‘PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig 

export PKG_CONFIG_PATH ’ >> /etc/bash.bashrc
    apt-get install libgtk2.0-dev 
    apt-get install cmake
    apt-get install pkg-config
    apt-get install Python-numpy

