#! /bin/bash

mkdir build && cd build
cmake ..
make -j8
sudo make -j8 install
