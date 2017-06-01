#ifndef COMUNICATION_H
#define COMUNICATION_H

#include "driver.h"
#include "data.h"

struct ZSTAR3 {
	struct port_device usbstick;
	struct data parameters;		//inicializar esse struct como zero;
};

void Rxyz(struct ZSTAR3 *usb_dev);
void Get_Data_Rate(struct ZSTAR3 *usb_dev);
void Change_Focus(struct ZSTAR3 *usb_dev);
void Set_Data_Rate(struct ZSTAR3 *usb_dev, int rate);
void Handshake_8b(struct ZSTAR3 *usb_dev);
void Read_register(struct ZSTAR3 *usb_dev);
void Send_Command(int *fd, char *ZCOMMAND, char *buffer);

#endif