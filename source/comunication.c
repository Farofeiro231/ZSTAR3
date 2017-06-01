#include "comunication.h"

void Handshake_8b(struct ZSTAR3 *usb_dev)
{
	/*Estabelece o modo de operação em 8 bits do sensor board
	Verifica que a conexão foi estabelecida com a placa*/
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND;
	int buffs = 2 * sizeof(char);
	ZCOMMAND = malloc (buffs);
	ZCOMMAND[0] = 0xA0;
	ZCOMMAND[1] = 0x6F;
	write(fd, ZCOMMAND, buffs);
	tcdrain(fd);
	printf("%s", ZCOMMAND);
	printf("Saindo da função Handshake_8b!\n");
	free(ZCOMMAND);
	ZCOMMAND = NULL;
}

void Change_Focus(struct ZSTAR3 *usb_dev)
{
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND, *buffer;
	ZCOMMAND = malloc (2 * sizeof(char));
	buffer = malloc (BUFFSIZE * sizeof(char));

	for (int i = 0; i < BUFFSIZE; i++) 
		buffer[i]=0;

	//printf("BUFFER: %s \n", buffer);
	ZCOMMAND[0] = 'N';
	ZCOMMAND[1] = '0';

	write(fd, ZCOMMAND, 2 * sizeof(char));
	tcdrain(fd);
	read(fd, buffer, BUFFSIZE * sizeof(char));

	printf("Index selecionado: %s \n", buffer);
	free(ZCOMMAND);
	free(buffer);
	buffer = NULL;
	ZCOMMAND = NULL;
}

void Get_Data_Rate(struct ZSTAR3 *usb_dev)
{
	int fd = get_fd(&usb_dev->usbstick);
	int count = 0;
	char *ZCOMMAND, *buffer;
	ZCOMMAND = malloc (sizeof(char));
	buffer = malloc (BUFFSIZE * sizeof(char));
	init_buffer(&(*buffer));

	ZCOMMAND[0] = 'm';

	tcflush(fd, TCIOFLUSH);
	write(fd, ZCOMMAND, sizeof(char));
	tcdrain(fd);
	count = read(fd, buffer, BUFFSIZE * sizeof(char));

	printf("Valor de count: %d \n", count);
	printf("data_rate: %s \n", buffer);
	free(ZCOMMAND);
	free(buffer);
	buffer = NULL;
	ZCOMMAND = NULL;

}


void Read_register(struct ZSTAR3 *usb_dev)
{
	int reg_addr;
	printf("Digite o endereço do registrador em decimal:");
	scanf("%d", &reg_addr);
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND, *buffer, *extended;
	ZCOMMAND = malloc (3 * sizeof(char));
	buffer = malloc (BUFFSIZE * sizeof(char));
	extended = malloc (BUFFSIZE * sizeof(char));
	init_buffer(&(*buffer));
	init_buffer(&(*extended));
	ZCOMMAND[0] = 'j';
	ZCOMMAND[1] = reg_addr;
	ZCOMMAND[2] = '1';

	printf("Comando: %d \n", ZCOMMAND[1]);
	Send_Command(&fd, &(*ZCOMMAND), &(*buffer));
	
	read(fd, extended, BUFFSIZE * sizeof(char));

	printf("Valor recebido: %s \n", buffer);
	printf("Valor extendido: %s \n", extended);
	usleep(31250);
}

void Send_Command(int *fd, char *ZCOMMAND, char *buffer)
{
	int FD = *fd;
	int count, i, recebido = 0;
	tcflush(FD, TCOFLUSH);
	write(FD, ZCOMMAND, 3 * sizeof(char));
	tcdrain(FD);
	
	while (recebido == 0) {
		
		count = read(FD, buffer, BUFFSIZE * sizeof(char));
		printf("Valor de count do while: %d \n", count);
		i++;
		
		if (count != 0) {
			recebido = 1;
		}

		if (count == 0 && i == 2) {
			write(FD, ZCOMMAND, 3 * sizeof(char));
			tcdrain(FD);
			i = 0;
		}
	}
}


void Set_Data_Rate(struct ZSTAR3 *usb_dev, int rate)
{
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND, *buffer;
	buffer = malloc (BUFFSIZE * sizeof(char));
	ZCOMMAND = malloc (2 * sizeof(char));
	ZCOMMAND[0] = 0x4D;		//M character to set new data rate
	ZCOMMAND[1] = 0x32;
	init_buffer(&(*buffer));

	switch(rate) {
		case(120):
			ZCOMMAND[1]=0x30;
		break;

		case(64):
			ZCOMMAND[1]=0x31;
			//printf("Data rate selecionado: 64\n");
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


	/* O buffer aqui está cheio de lixo. Tenho que limpá-lo antes */
	//printf("Buffer antes de enviar o ZCOMMAND: %s \n", buffer);
	//printf("Valor de ZCOMMAND: %s  \n", ZCOMMAND);
	write(fd, ZCOMMAND, 2 * sizeof(char));
	tcdrain(fd);
	//printf("Valor de buffer2: %s \n", buffer);
	read(fd, buffer, BUFFSIZE * sizeof(char));
	printf("Buffer lido %s \n",buffer);

	free(ZCOMMAND);
	free(buffer);
	//tcflush(fd, TCIOFLUSH);
	buffer = NULL;
	ZCOMMAND = NULL;
	usleep(31250);

}

void Rxyz(struct ZSTAR3 *usb_dev)
{
	struct timeval t1, t2;
	double delta_t;
	int fd = get_fd(&usb_dev->usbstick);
	printf("Entrei na função Rxyz!\n");
	char *buffer, *ZCOMMAND;
	ZCOMMAND = malloc (sizeof(char));
	buffer = malloc (6 * sizeof(char) );
	ZCOMMAND[0] = 0x56;
	
	//printf("get_fd(usb_dev.usbstick):%d)\n", get_fd(usb_dev.usbstick));
	gettimeofday(&t1, NULL);
	write(fd, ZCOMMAND, sizeof(char));
	tcdrain(fd);
	read(fd, buffer, 6 * sizeof(char));
	gettimeofday(&t2, NULL);
	delta_t = t2.tv_usec - t1.tv_usec;	

	/*Medindo o tempo que leva entre a escrita/tx
	* e a recepção / leitura dos dados */
	printf("Tempo tx/rx: %f \n", delta_t);

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