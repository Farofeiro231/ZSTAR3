#include "comunication.h"

void ZSTAR3::Handshake_8b()
{
	/*Estabelece o modo de operação em 8 bits do sensor board
	Verifica que a conexão foi estabelecida com a placa*/

	char* ZCOMMAND;
	ZCOMMAND = malloc (sizeof(char));
	ZCOMMAND[]={0x52};
	write(usbstick.get_fd(), ZCOMMAND, sizeof(ZCOMMAND));
	tcdrain(usbstick.get_fd());

	free(ZCOMMAND);
	ZCOMMAND = NULL;
}

void ZSTAR3::Set_Data_Rate(int rate)
{
	char* ZCOMMAND;
	ZCOMMAND = malloc (2 * sizeof(char));
	ZCOMMAND[] = {0x4D, 0x31};
	
	switch(rate){
		case(30):
			ZCOMMAND[1]={0x31}
		break;

		case(60):
			ZCOMMAND[1]={0x32};
		break;

		case(120):
			ZCOMMAND[1]={0x30}
		break;
			printf("Invalid rate value.\n");
		default:
	}

	write(usbstick.get_fd(), ZCOMMAND, sizeof(ZCOMMAND));
	tcdrain(usbstick.get_fd());

	free(ZCOMMAND);
	ZCOMMAND = NULL;
}

ZSTAR3::Rxyz()
{
	char* buffer, ZCOMMAND;
	ZCOMMAND = malloc (sizeof(char));
	buffer = malloc (6 * sizeof(char) );
	ZCOMMAND[] = {0x56};

	write(usbstick.get_fd(), ZCOMMAND, sizeof(ZCOMMAND));
	tcdrain(usbstick.get_fd());
	read(usbstick.get_fd(), buffer, sizeof(buffer));

	/*Terminar essa função!!!*/

}