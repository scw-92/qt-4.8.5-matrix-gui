#!/bin/sh

if test -e /dev/fb0; then
width=`fbset | grep 'geometry' | awk '{print $2}'`
height=`fbset | grep 'geometry' | awk '{print $3}'`

let height=height-38
geo=`echo $width\x$height+0+0`
fi
#export QWS_DISPLAY='Transformed:Rot90'
if [ $? == 0 ]
then
       cd  /usr/share/qt/bin/dialcontrol
	./dialcontrol -geometry $geo $*
	cd -
else

export TSLIB_TSDEVICE=/dev/input/event0
export QWS_MOUSE_PROTO=Tslib:/dev/input/event0
        /usr/share/qt/bin/dialcontrol/dialcontrol -qws -geometry $geo $*
fi
