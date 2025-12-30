#!/bin/sh -x

ROOT_DIR=$(dirname $0)/..

cd ${ROOT_DIR}

for i in src/*; do (cd ${i}; ./clean.sh); done
