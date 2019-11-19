#!/bin/bash

PACKAGE_NAME=pi_pedal.zip
TARGET=../pi_pedal/
USERNAME=pi
IP=192.168.1.198

./clean.sh
cd ..
touch revision
git rev-parse --short HEAD > revision
zip -r ${PACKAGE_NAME} ${TARGET}
scp ${PACKAGE_NAME} ${USERNAME}@${IP}:/home/${USERNAME}
rm -rvf ${PACKAGE_NAME}
rm -rvf revision

