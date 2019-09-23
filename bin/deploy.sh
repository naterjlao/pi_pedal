#!/bin/bash

PACKAGE_NAME=pi_pedal.zip
TARGET=../pi_pedal/

if ["$1" != ""]; then
	USERNAME=pi
	IP=192.168.1.198
else
	USERNAME=nlao
	IP=192.168.56.3
fi

./clean.sh
cd ..
zip -r ${PACKAGE_NAME} ${TARGET}
scp ${PACKAGE_NAME} ${USERNAME}@${IP}:/home/${USERNAME}
rm -rvf ${PACKAGE_NAME}

