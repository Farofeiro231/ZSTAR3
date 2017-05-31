#include "comunication.h"

void Handshake_8b(struct ZSTAR3 usb_dev)
{
	/*Estabelece o modo de operação em 8 bits do sensor board
	Verifica que a conexão foi estabelecida com a placa*/

	char *ZCOMMAND;
	int buffs = sizeof(char);
	ZCOMMAND = malloc (buffs);
	ZCOMMAND[0] = 0x52;
	write(get_fd(&usb_dev.usbstick), ZCOMMAND, buffs);
	tcdrain(get_fd(&usb_dev.usbstick));
	printf("Saindo da função Handshake_8b!\n");
	free(ZCOMMAND);
	ZCOMMAND = NULL;
}

void Get_Data_Rate(struct ZSTAR3 *usb_dev)
{
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND, *buffer;
	ZCOMMAND = malloc (sizeof(char));
	buffer = malloc (sizeof(char));
	ZCOMMAND[0] = 'm';

	write(fd, ZCOMMAND, sizeof(char));
	tcdrain(fd);
	read(fd, buffer, sizeof(char));

	printf("data_rate: %s \n", buffer);
	free(ZCOMMAND);
	free(buffer);
	buffer = NULL;
	ZCOMMAND = NULL;

}

void Set_Data_Rate(struct ZSTAR3 *usb_dev, int rate)
{
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND, *buffer;
	buffer = malloc (2 * sizeof(char));
	ZCOMMAND = malloc (2 * sizeof(char));
	ZCOMMAND[0] = 0x4D;		//M character to set new data rate
	ZCOMMAND[1] = 0x32;



	switch(rate) {
		case(120):
			ZCOMMAND[1]=0x30;
		break;

		case(64):
			ZCOMMAND[1]=0x31;
			printf("Data rate selecionado: 64\n");
		break;

		case(32):
			ZCOMMAND[1]=0x32;
		break;
		
		case(16):
			ZCOMMAND[1]=0x33;
		break;

		case(8):
			ZCOMMAND[1]=0x34;
		break;

		case(4):
			ZCOMMAND[1]=0x35;
		break;

		case(2):
			ZCOMMAND[1]=0x36;
		break;

		case(1):
			ZCOMMAND[1]=0x37;
		break;

		default:
			printf("Invalid rate value.\n");
		break;
	}

	printf("Valor de ZCOMMAND: %s  \n", ZCOMMAND);
	write(fd, ZCOMMAND, 2 * sizeof(char));
	tcdrain(fd);
	read(fd, buffer, 2 * sizeof(char));
	printf("Valor de buffer: %s \n", buffer);

	free(ZCOMMAND);
	free(buffer);
	buffer = NULL;
	ZCOMMAND = NULL;
	//tcflush(fd, TCIOFLUSH);
	usleep(31250);

}

void Rxyz(struct ZSTAR3 *usb_dev)
{
	int fd;
	fd = get_fd(&usb_dev->usbstick);
	printf("Entrei na função Rxyz!\n");
	char *buffer, *ZCOMMAND;
	ZCOMMAND = malloc (sizeof(char));
	buffer = malloc (6* sizeof(char) );
	ZCOMMAND[0] = 0x56;
	
	//printf("get_fd(usb_dev.usbstick):%d)\n", get_fd(usb_dev.usbstick));

	write(fd, ZCOMMAND, sizeof(char));
	tcdrain(fd);
	read(fd, buffer, 6 * sizeof(char));
	
	usb_dev->parameters.Acc_x = (double) buffer[1] /22.0;
	usb_dev->parameters.Acc_y = (double) buffer[3] /22.0;
	usb_dev->parameters.Acc_z = (double) buffer[5] /22.0;

	printf("Valor de aceleracao em x: %f \n", usb_dev->parameters.Acc_x);
	printf("Valor de aceleracao em y: %f \n", usb_dev->parameters.Acc_y);
	printf("Valor de aceleracao em z: %f \n", usb_dev->parameters.Acc_z);
	
	free(buffer);
	free(ZCOMMAND);
	buffer = NULL;
	ZCOMMAND = NULL;

	usleep(31250);
}