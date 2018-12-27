#!/bin/sh
rm -rf /etc/pointercal

ts_calibrate
sync
sync
sync

kill $(pidof matrix_gui)

/qt_app/matrix_gui -qws 2>/dev/null  &
