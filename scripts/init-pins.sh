#! /bin/sh
### BEGIN INIT INFO
# Provides: inti-pins.sh
# Required-Start:
# Should-Start:
# Required-Stop:
# Default-Start: S
# Default-Stop:
# Short-Description: Configures Galileo for qser.
# Description: Configures Galileo for qser.
### END INIT INFO

		# INICIALIZACAO DE PINOS PARA GALILEO QSER

case "$1" in
	start|restart|force-reload)

    ## PONTE H
		#IO 3 - PWM
		if [ ! -d /sys/class/gpio/gpio64 ]; then echo -n "64" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio64/direction;	echo -n "1" > /sys/class/gpio/gpio64/value
		if [ ! -d /sys/class/gpio/gpio76 ]; then echo -n "76" > /sys/class/gpio/export; fi
		echo -n "0" > /sys/class/gpio/gpio76/value
		if [ ! -d /sys/class/gpio/gpio17 ]; then echo -n "17" > /sys/class/gpio/export;	fi
		echo -n "in" > /sys/class/gpio/gpio17/direction
		if [ ! -d /sys/class/gpio/gpio16 ]; then echo -n "16" > /sys/class/gpio/export;	fi
		echo -n "out" > /sys/class/gpio/gpio16/direction;	echo -n "0" > /sys/class/gpio/gpio16/value
		if [ ! -d /sys/class/pwm/pwmchip0/pwm1 ]; then echo -n "1" > /sys/class/pwm/pwmchip0/export; fi
		chmod a+rw /sys/class/pwm/pwmchip0/pwm1/enable
		chmod a+rw /sys/class/pwm/pwmchip0/pwm1/duty_cycle
		chmod a+rw /sys/class/pwm/pwmchip0/device/pwm_period

		## PONTE H
		#IO 7 - Enable
		if [ ! -d /sys/class/gpio/gpio38 ]; then echo -n "38" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio38/direction
#		if [ ! -d /sys/class/gpio/gpio20 ]; then echo -n "20" > /sys/class/gpio/export; fi
#		echo -n "out" > /sys/class/gpio/gpio20/direction; echo -n "0" > /sys/class/gpio/gpio20/value
		if [ ! -d /sys/class/gpio/gpio39 ]; then echo -n "39" > /sys/class/gpio/export; fi
		echo -n "in" > /sys/class/gpio/gpio39/direction
#		if [ ! -d /sys/class/gpio/gpio68 ]; then echo -n "68" > /sys/class/gpio/export; fi
#		echo -n "0" > /sys/class/gpio/gpio68/value
		chmod a+rw /sys/class/gpio/gpio38/value

		##SPI
    chmod a+rw /dev/spidev1.0

		#IO 10
		if [ ! -d /sys/class/gpio/gpio10 ] ; then echo -n "10" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio10/direction
		if [ ! -d /sys/class/gpio/gpio26 ] ; then echo -n "26" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio26/direction; echo -n "0" > /sys/class/gpio/gpio26/value
		if [ ! -d /sys/class/gpio/gpio27 ] ; then echo -n "27" > /sys/class/gpio/export; fi
		echo -n "in" > /sys/class/gpio/gpio27/direction
		if [ ! -d /sys/class/gpio/gpio74 ] ; then echo -n "74" > /sys/class/gpio/export; fi
		echo -n "0" > /sys/class/gpio/gpio74/value
		chmod a+rw /sys/class/gpio/gpio10/value

		#IO 11
		if [ ! -d /sys/class/gpio/gpio24 ] ; then echo -n "24" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio24/direction;	echo -n "0" > /sys/class/gpio/gpio24/value
		if [ ! -d /sys/class/gpio/gpio25 ] ; then echo -n "25" > /sys/class/gpio/export; fi
		echo -n "in" > /sys/class/gpio/gpio25/direction
		if [ ! -d /sys/class/gpio/gpio44 ] ; then echo -n "44" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio44/direction;	echo -n "1" > /sys/class/gpio/gpio44/value
		if [ ! -d /sys/class/gpio/gpio72 ] ; then echo -n "72" > /sys/class/gpio/export; fi
		echo -n "0" > /sys/class/gpio/gpio72/value
		chmod a+rw /sys/class/gpio/gpio24/value

		#IO 12
		if [ ! -d /sys/class/gpio/gpio42 ] ; then echo -n "42" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio42/direction;	echo -n "1" > /sys/class/gpio/gpio42/value
		if [ ! -d /sys/class/gpio/gpio43 ] ; then echo -n "43" > /sys/class/gpio/export; fi
		echo -n "in" > /sys/class/gpio/gpio43/direction
		chmod a+rw /sys/class/gpio/gpio24/value

		#IO 13
		if [ ! -d /sys/class/gpio/gpio30 ] ; then echo -n "30" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio30/direction;	echo -n "0" > /sys/class/gpio/gpio30/value
		if [ ! -d /sys/class/gpio/gpio31 ] ; then echo -n "31" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio31/direction;	echo -n "0" > /sys/class/gpio/gpio31/value
		if [ ! -d /sys/class/gpio/gpio46 ] ; then echo -n "46" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio46/direction;	echo -n "1" > /sys/class/gpio/gpio46/value
    chmod a+rw /sys/class/gpio/gpio30/value


		## FINAL DE CURSO
		#IO 5
		if [ ! -d /sys/class/gpio/gpio0 ]; then echo -n "0" > /sys/class/gpio/export; fi
		echo -n "in" > /sys/class/gpio/gpio0/direction
		if [ ! -d /sys/class/gpio/gpio18 ]; then echo -n "18" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio18/direction; echo -n "1" > /sys/class/gpio/gpio18/value
		if [ ! -d /sys/class/gpio/gpio19 ]; then echo -n "19" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio19/direction; echo -n "1" > /sys/class/gpio/gpio19/value
		if [ ! -d /sys/class/gpio/gpio66 ]; then echo -n "66" > /sys/class/gpio/export; fi
		echo -n "0" > /sys/class/gpio/gpio66/value
		chmod a+rw /sys/class/gpio/gpio0/value

		# IO 4
		if [ ! -d /sys/class/gpio/gpio6 ]; then echo -n "6" > /sys/class/gpio/export; fi
		echo -n "in" > /sys/class/gpio/gpio6/direction
		if [ ! -d /sys/class/gpio/gpio36 ]; then echo -n "36" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio36/direction; echo -n "1" > /sys/class/gpio/gpio36/value
		if [ ! -d /sys/class/gpio/gpio37 ]; then echo -n "37" > /sys/class/gpio/export; fi
		echo -n "out" > /sys/class/gpio/gpio37/direction; echo -n "1" > /sys/class/gpio/gpio37/value
		chmod a+rw /sys/class/gpio/gpio6/value
	;;

	stop)

	  #IO 3
		echo -n "64" > /sys/class/gpio/unexport
		echo -n "76" > /sys/class/gpio/unexport
		echo -n "in" > /sys/class/gpio/gpio17/direction
		echo -n "17" > /sys/class/gpio/unexport
		echo -n "16" > /sys/class/gpio/unexport
		echo -n "1" > /sys/class/pwm/pwmchip0/unexport

		#IO 4
		echo -n "6" > /sys/class/gpio/unexport
		echo -n "36" > /sys/class/gpio/unexport
		echo -n "in" > /sys/class/gpio/gpio37/direction
		echo -n "37" > /sys/class/gpio/unexport

		#IO 5
		echo -n "0" > /sys/class/gpio/unexport
		echo -n "18" > /sys/class/gpio/unexport
		echo -n "in" > /sys/class/gpio/gpio19/direction
		echo -n "19" > /sys/class/gpio/unexport
		echo -n "66" > /sys/class/gpio/unexport

		#IO 10
		echo -n "10" > /sys/class/gpio/unexport
		echo -n "in" > /sys/class/gpio/gpio27/direction
		echo -n "27" > /sys/class/gpio/unexport
		echo -n "26" > /sys/class/gpio/unexport
		echo -n "74" > /sys/class/gpio/unexport

		#IO 11
		echo -n "24" > /sys/class/gpio/unexport
		echo -n "in" > /sys/class/gpio/gpio25/direction
		echo -n "25" > /sys/class/gpio/unexport
		echo -n "44" > /sys/class/gpio/unexport
		echo -n "72" > /sys/class/gpio/unexport

		#IO 12
		echo -n "42" > /sys/class/gpio/unexport
		echo -n "in" > /sys/class/gpio/gpio43/direction
		echo -n "43" > /sys/class/gpio/unexport

		#IO 13
		echo -n "30" > /sys/class/gpio/unexport
		echo -n "in" > /sys/class/gpio/gpio31/direction
		echo -n "31" > /sys/class/gpio/unexport
		echo -n "46" > /sys/class/gpio/unexport
	;;
	status)
		ls -d /sys/class/gpio/gpio*
	;;
	*)
		echo -n "Usage: $0 {start|stop|restart|force-reload|status}"
		exit 1
	;;
esac
exit 0