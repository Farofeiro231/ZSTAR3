#ifndef DRIVER_H
#define DRIVER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h> /* POSIX terminal control definitons*/

#define USBDEVICE "/dev/ttyACM0"

/*http://www.cmrr.umn.edu/~strupp/serial.html - Site para comunicações seriais*/

/*A cada 33.33 ms novos dados são recebidos pelos sensores (30 Hz) - por padrão*/

struct port_device {
	int fd;
};

void init_fd(struct port_device usbstick);
void config_fd(struct port_device usbstick);
int get_fd(struct port_device usbstick);
void close_fd(struct port_device usbstick);

#endif