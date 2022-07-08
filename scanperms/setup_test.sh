#!/bin/bash
set -xe
mkdir test
cd test
touch 000-normal.txt
touch 006-bothneg.txt
touch 060-userneg.txt
touch 066-userneg.txt
touch 600-normal.txt
touch 606-groupneg.txt
touch 660-normal.txt
touch 666-normal.txt
chmod 000 000-normal.txt
chmod 006 006-bothneg.txt
chmod 060 060-userneg.txt
chmod 066 066-userneg.txt
chmod 600 600-normal.txt
chmod 606 606-groupneg.txt
chmod 660 660-normal.txt
chmod 666 666-normal.txt 