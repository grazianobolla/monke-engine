# !/bin/bash

scons -j4
echo Installing library file...
sudo cp libmonke.a /usr/local/lib
echo Installing library headers...
sudo cp -r include/monke/ /usr/local/include/