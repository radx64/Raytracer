#!/bin/bash
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make -j`echo $(nproc)` test