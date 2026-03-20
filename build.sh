#!/bin/bash

source /home/share/rk3588_env

if test -z $1
then
    BUILD_TYPE=Debug
else
    BUILD_TYPE=$1
fi
if test ${BUILD_TYPE} = "Release"
then 
    STRIP_CMD="/strip"
    mkdir -p release/version
else
    STRIP_CMD=""
fi

printf "=============================== \n"
printf "BUILD_TYPE = %s, STRIP_CMD = %s \n" ${BUILD_TYPE} ${STRIP_CMD}
printf "=============================== \n"


printf "=============================== \n"
printf "build appfw begin\n"
printf "=============================== \n"
cd appfw
mkdir build
cd build
cmake -DCMAKE_NO_SYSTEM_FROM_IMPORTED=1 -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_SYSROOT=/home/share/rk3588_sdk/aarch64-buildroot-linux-gnu/sysroot/ ..
make
DESTDIR=${SDKTARGETSYSROOT} make install${STRIP_CMD}
DESTDIR=../../release make install${STRIP_CMD}

if test ${BUILD_TYPE} = "Release"
then 
    git rev-parse HEAD > ../../release/version/appfw_version
fi
cd ../../

printf "=============================== \n"
printf "build appfw end \n"
printf "=============================== \n"


printf "=============================== \n"
printf "build HMIControllers begin \n"
printf "=============================== \n"
cd HMIControllers
mkdir build
cd build
cmake -DCMAKE_NO_SYSTEM_FROM_IMPORTED=1 -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_SYSROOT=/home/share/rk3588_sdk/aarch64-buildroot-linux-gnu/sysroot/ ..
make
DESTDIR=${SDKTARGETSYSROOT} make install${STRIP_CMD}
DESTDIR=../../release make install${STRIP_CMD}

if test ${BUILD_TYPE} = "Release"
then 
    git rev-parse HEAD > ../../release/version/HMIControllers_version
fi
cd ../../

printf "=============================== \n"
printf "build HMIControllers end \n"
printf "=============================== \n"

printf "=============================== \n"
printf "build HMI begin \n"
printf "=============================== \n"
cd HMI
mkdir build
cd build
/home/share/rk3568_sdk/bin/qmake ..
make -j4
DESTDIR=${SDKTARGETSYSROOT} make install
DESTDIR=../../release make install

if test ${BUILD_TYPE} = "Release"
then 
    git rev-parse HEAD > ../../release/version/HMI_version
fi
cd ../../

printf "=============================== \n"
printf "build HMI end \n"
printf "=============================== \n"

mkdir -p release/lib/systemd/system
cp -a systemd_service/* release/lib/systemd/system

if test ${BUILD_TYPE} = "Release"
then 
    cd release
    tar zcvf RaiteClusterApp.tar.gz *
    cd ..
fi

printf "=============================== \n"
printf "build all end \n"
printf "=============================== \n"
