#! /bin/sh
### BEGIN INIT INFO
# Provides:          lumian
# Required-Start:    
# Required-Stop:
# Default-Start:     99
# Default-Stop:
# Short-Description: executed by init(8) upon entering runlevel 5.
### END INIT INFO

do_start () {
  ### Print System Information
  echo "============================"
  echo "who -r: `who -r`"
  echo "current time: `date`"
  echo "uptime: `uptime`"
  echo "runlevel: `runlevel`"
  echo "who: `whoami`"
  echo "\n"

  ### Start Process
  cd /path/to/
  nohup ./start_app.sh >/dev/null 2>&1 &

  ### Start Script
  su - lumian -c '/path/to/script.sh &'
}

case "$1" in
  start)
	do_start
	;;
  restart|reload|force-reload)
	echo "Error: argument '$1' not supported" >&2
	exit 3
	;;
  stop|status)
	# No-op
	;;
  *)
	echo "Usage: $0 start|stop" >&2
	exit 3
	;;
esac
