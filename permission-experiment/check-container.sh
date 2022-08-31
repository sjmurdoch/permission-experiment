#!/bin/sh

UID_PATTERN='^Uid:[[:space:]]+101[[:space:]]+101[[:space:]]+101[[:space:]]+101[[:space:]]*$'
GID_PATTERN='^Gid:[[:space:]]+101[[:space:]]+101[[:space:]]+101[[:space:]]+101[[:space:]]*$'
GROUP_PATTERN_OK='^Groups:[[:space:]]+101[[:space:]]+1001[[:space:]]*$'
GROUP_PATTERN_VULN='^Groups:[[:space:]]+1001[[:space:]]*$'
DEBUG_PATTERN='^(Uid|Gid|Groups):[[:space:]]+'
STATUS_FILENAME="/02-error.html"

if ! egrep -q $UID_PATTERN /proc/$$/status; then
    echo "### The presence of the negative-group permissions vulnerability could not be checked because an unexpected result was obtained in checking the user ID."
    exit
fi

if ! egrep -q $GID_PATTERN /proc/$$/status; then
    echo "### The presence of the negative-group permissions vulnerability could not be checked because an unexpected result was obtained in checking the group ID."
    exit
fi

if egrep -q $GROUP_PATTERN_OK /proc/$$/status; then
    echo "### Your container runtime appears to be not be affected by the negative-group permissions vulnerability because it handles supplementary groups correctly."
    STATUS_FILENAME="02-ok.html"
elif egrep -q $GROUP_PATTERN_VULN /proc/$$/status; then
    echo "###  Your container runtime appears to be affected by the negative-group permissions vulnerability because it does not handle supplementary groups correctly."
    STATUS_FILENAME="02-fail.html"
else
    echo "### The presence of the negative-group permissions vulnerability could not be checked because an unexpected result was obtained in checking the supplementary groups."
fi

cat /01-head.html $STATUS_FILENAME /03-debughead.html > /usr/share/nginx/html/index.html
egrep $DEBUG_PATTERN /proc/$$/status >> /usr/share/nginx/html/index.html
cat /04-debugfoot.html >> /usr/share/nginx/html/index.html 