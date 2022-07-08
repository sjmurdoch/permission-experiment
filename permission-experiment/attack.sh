#!/bin/sh

ls -l
id
./mycat sekrit.txt
cp mycat mycat_g
chgrp 1001 mycat_g
chmod g+s mycat_g
./mycat_g sekrit.txt
