#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h> /* POSIX terminal control definitons*/

#define USBDEVICE "/dev/ttyS0"

/*http://www.cmrr.umn.edu/~strupp/serial.html - Site para comunicações seriais*/

/*A cada 33.33 ms novos dados são recebidos pelos sensores (30 Hz) - por padrão*/

struct port_device {
	int fd;
	int init_fd ();
	int config_fd();
	int get_fd();
	void close_fd();
};

#endif