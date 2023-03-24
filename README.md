
# platform

    1. mac only has stub
    2. linux has OpenGL and EGL

# build and test c++

    ./build.sh 

# build and test java

    ./buildjava.sh

# release files

    release/libglvndcontext.so
    release/java
        package project.android.fastimage.filter.soul;
        class SoulRenderLinuxJNI;

# build release
    
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=RELEASE
    make VERBOSE=1

# prerequisite

    // gpu and driver
    NVIDIA GPU
    NVIDIA driver that support GLVND
    
    // c++ build tools
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc
    sudo apt install clang
    sudo apt install make
    sudo apt install cmake

    // java build and run tools
    sudo apt-get install openjdk-8-jdk
    sudo vi ~/.bashrc
        export JAVA_HOME="/usr/lib/jvm/java-8-openjdk-amd64/"
        export PATH=$PATH:$JAVA_HOME/bin
    source ~/.bashrc

