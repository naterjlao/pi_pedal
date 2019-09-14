#!/bin/bash

PACKAGE_NAME=pi_pedal.zip
TARGET=../pi_pedal/
USERNAME=pi
IP=192.168.1.198

./clean.sh
cd ..
zip -r ${PACKAGE_NAME} ${TARGET}
scp ${PACKAGE_NAME} ${USERNAME}@${IP}:/home/${USERNAME}
rm -rvf ${PACKAGE_NAME}

