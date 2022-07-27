#!/bin/sh

set -x
: "### Operating system"
cat /etc/os-release
: "### Listing files"
cd /app
ls -ln
: "### Current user and groups (from id)"
id
: "### Current user and groups (from permutil)"
./permutil -p
: "### Attempt to open the restricted file (will fail)"
./permutil -c sekrit.txt
: "### Create a setgid executable"
cp permutil permutil-sgid
chgrp 1001 permutil-sgid
chmod g+s permutil-sgid
ls -ln permutil-sgid
: "### Use the setgid executable file to open the restricted file"
./permutil-sgid -p
./permutil-sgid -c sekrit.txt
