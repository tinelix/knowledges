#!/bin/bash

make -j8 && make install

cd ..
make

echo
echo "Build completed!"
echo
echo "Run './out/knowlegdes' for testing, 'gdb ./out/knowlegdes' + 'r' for debug"
cd ./out
