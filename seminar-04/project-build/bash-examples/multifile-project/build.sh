#!/bin/bash

CFLAGS="-std=c++11 -Wall"

SOURCE_DIR=src
BUILD_DIR=build

mkdir -p ${BUILD_DIR}
g++ ${CFLAGS} -o ${BUILD_DIR}/HelloWorldClass.o -c ${SOURCE_DIR}/HelloWorldClass.cpp
g++ ${CFLAGS} -o ${BUILD_DIR}/main.o -c ${SOURCE_DIR}/main.cpp
g++ ${CFLAGS} -o HelloWorldClassProject ${BUILD_DIR}/main.o ${BUILD_DIR}/HelloWorldClass.o
