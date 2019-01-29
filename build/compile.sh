#!/bin/sh

sudo mount -t drvfs D: /mnt/d
make
cp /mnt/e/gitwerk/EMSYS_Project/build/kernel.img /mnt/d/kernel.img
sudo umount /mnt/d
