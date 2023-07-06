#!/bin/bash

# Testando a criação do shellscript para instalar as dependencias do projeto
sudo apt install python2
sudo apt-get install Cmake
git clone https://github.com/cocos2d/cocos2d-x.git
cd cocos2d-x
python2 download-deps.py
python2 setup.py
source FILE_TO_SAVE_SYSTEM_VARIABLE
./install-linux-deps.sh
chmod +x ~/.cocos2d-x-3.13.1/tools/cocos2d-console/bin/cocos
cd ../
cocos compile -s ./ -p linux -m release -o ./bin