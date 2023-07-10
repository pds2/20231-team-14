#!/bin/bash

if [ -d "linux-build" ] 
then
    echo " "
else
    cocos compile -s ./ -p linux -m release -o ./bin
fi

cocos run -s ./ -p linux