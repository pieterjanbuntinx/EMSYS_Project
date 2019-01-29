#!/bin/sh

sudo mount -t drvfs E: /mnt/e
make
cp /mnt/c/Users/piete/Documents/Git/EMSYS_Project_ToF_sensor/build/kernel.img /mnt/e/kernel.img
sudo umount /mnt/e
