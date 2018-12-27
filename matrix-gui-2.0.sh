#! /bin/sh

matrixgui="/usr/bin/matrix_browser"
GUI_OPTS="http://localhost:80/ """
PIDFILE="/var/run/matrix-gui-2.0.pid"

# Important System Environment Variables
for sh in /etc/profile.d/*.sh ; do
    [ -r "$sh" ] && . "$sh"
done

test -x "$matrixgui" || exit 0

case "$1" in
  start)
    

    #Clear out the the tmp and lock directory
    cd /usr/share/matrix-gui-2.0
    rm -rf tmp/*
    rm -rf lock/*
    cd -

	if [ -e $PIDFILE ]; then
      PIDDIR=/proc/$(cat $PIDFILE)
      if [ -d ${PIDDIR} -a  "$(readlink -f ${PIDDIR}/exe)" = "${matrixgui}" ]; then
        echo "$DESC already started; not starting."
      else
        echo "Removing stale PID file $PIDFILE."
        rm -f $PIDFILE
      fi
    fi

    echo -n "Starting Matrix GUI application"
    start-stop-daemon --start --quiet --background -m --pidfile $PIDFILE --exec $matrixgui -- $GUI_OPTS
    echo "."
    ;;

  stop)
    echo -n "Stopping Matrix GUI application"
    start-stop-daemon --stop --quiet --pidfile $PIDFILE
    echo "."
    ;;
  *)
    echo "Usage: /etc/init.d/matrix-gui-2.0 {start|stop}"
    exit 1
esac

exit 0
