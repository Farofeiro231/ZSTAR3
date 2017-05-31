#include "comunication.h"

void Handshake_8b(struct ZSTAR3 usb_dev)
{
	/*Estabelece o modo de operação em 8 bits do sensor board
	Verifica que a conexão foi estabelecida com a placa*/

	char *ZCOMMAND;
	int buffs = sizeof(char);
	ZCOMMAND = malloc (buffs);
	ZCOMMAND[0] = 0x52;
	write(get_fd(usb_dev.usbstick), ZCOMMAND, buffs);
	tcdrain(get_fd(usb_dev.usbstick));
	printf("Saindo da função Handshake_8b!\n");
	free(ZCOMMAND);
	ZCOMMAND = NULL;
}

void Set_Data_Rate(struct ZSTAR3 usb_dev, int rate)
{
	char *ZCOMMAND;
	ZCOMMAND = malloc (2 * sizeof(char));
	ZCOMMAND[0,1] = 0x4D, 0x31;
	
	switch(rate) {
		case(120):
			ZCOMMAND[1]=0x30;
		break;

		case(64):
			ZCOMMAND[1]=0x31;
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

	write(get_fd(usb_dev.usbstick), ZCOMMAND, sizeof(ZCOMMAND));
	tcdrain(get_fd(usb_dev.usbstick));

	free(ZCOMMAND);
	ZCOMMAND = NULL;
}

void Rxyz(struct ZSTAR3 usb_dev)
{
	printf("Entrei na função Rxyz!\n");
	char *buffer, *ZCOMMAND;
	ZCOMMAND = malloc (sizeof(char));
	buffer = malloc (1024 * sizeof(char) );
	ZCOMMAND[0] = 0x56;
	write(get_fd(usb_dev.usbstick), ZCOMMAND, sizeof(char));
	tcdrain(get_fd(usb_dev.usbstick));
	printf("Passei do tcdrain do envio!\n");
	fflush(stdout);
	read(get_fd(usb_dev.usbstick), buffer, 1024 * sizeof(char));
	printf("Passei da leitura!\n");
	/*Terminar essa função!!!*/

	usb_dev.parameters.Acc_x = (double) buffer[1];
	usb_dev.parameters.Acc_x = (double) buffer[3];
	usb_dev.parameters.Acc_x = (double) buffer[5];

	printf("Valor de aceleracao em x: %f \n", usb_dev.parameters.Acc_x);
	printf("Valor de aceleracao em y: %f \n", usb_dev.parameters.Acc_y);
	printf("Valor de aceleracao em z: %f \n", usb_dev.parameters.Acc_z);

	free(buffer);
	free(ZCOMMAND);
	buffer = NULL;
	ZCOMMAND = NULL;
}