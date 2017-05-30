#ifndef COMUNICATION_H
#define COMUNICATION_H

#include "driver.h"
#include "data.h"

struct ZSTAR3{
	struct port_device usbstick;
	struct data parameters;
	Handshake_8b();
	Set_Data_Rate(int rate);
	Rxyz();
};

#endif