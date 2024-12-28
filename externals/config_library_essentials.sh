#! /bin/bash

rm -rf ./packages
rm -rf ./paho.mqtt.cpp

git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
git checkout v1.4.0
git submodule init
git submodule update
cmake -Bbuild -H. -DPAHO_WITH_MQTT_C=ON -DPAHO_BUILD_EXAMPLES=ON -DPAHO_WITH_SSL=TRUE -DCMAKE_INSTALL_PREFIX=../packages/




#cmake -Bbuild -H. -DPAHO_WITH_MQTT_C=ON -DPAHO_BUILD_EXAMPLES=ON -DCMAKE_TOOLCHAIN_FILE=../toolchains/cmake/toolchain_imx6.cmake
cmake --build build/ --target install
