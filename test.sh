#!/bin/sh

PROG=./dog

X="hello world"
Y="hello again, pretty world!"
Z=<<EOF
hello for a third time
now have

some newlines or whatever



EOF

XN=$(echo $X | $PROG)
XO=$(cat $XN)
[ x"$X" = x"$XO" ] || (echo "fail 1" &>2 && exit 1)
rm -f $XN

YN=$(echo $Y | $PROG)
YO=$(cat $YN)
[ x"$Y" = x"$YO" ] || (echo "fail 2" &>2 && exit 1)
rm -f $YN

ZN=$(echo $Z | $PROG)
ZO=$(cat $ZN)
[ x"$Z" = x"$ZO" ] || (echo "fail 3" &>2 && exit 1)
rm -f $ZN

exit 0

