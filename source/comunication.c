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
	init_buffer(&(*buffer));


	//printf("BUFFER: %s \n", buffer);
	ZCOMMAND[0] = 'N';
	ZCOMMAND[1] = '0';

	Send_Command(&fd, &(*ZCOMMAND), &(*buffer), 2);
	printf("Valor lido do buffer: %s \n", buffer);
	free(ZCOMMAND);
	free(buffer);
	buffer = NULL;
	ZCOMMAND = NULL;
}

void Get_Data_Rate(struct ZSTAR3 *usb_dev)
{
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND, *buffer;
	ZCOMMAND = malloc (sizeof(char));
	buffer = malloc (BUFFSIZE * sizeof(char));
	init_buffer(&(*buffer));

	ZCOMMAND[0] = 'm';

	Send_Command(&fd, &(*ZCOMMAND), &(*buffer), 1);
	printf("Data rate lido: %s \n", buffer);
	free(ZCOMMAND);
	free(buffer);
	buffer = NULL;
	ZCOMMAND = NULL;
	usleep(31250);
}

/* Não usar essa função */
void Set_NetNum(struct ZSTAR3 *usb_dev)
{
	int fd = get_fd(&usb_dev->usbstick);
	char *ZCOMMAND, *buffer;
	ZCOMMAND = malloc (3 * sizeof(char));
	buffer = malloc (BUFFSIZE * sizeof(char));
	init_buffer(&(*buffer));

	ZCOMMAND[0] = 'h';
	ZCOMMAND[1] = 'U';
	ZCOMMAND[2] = 'm';

	Send_Command(&fd, &(*ZCOMMAND), &(*buffer), 3);
	printf("Data rate lido: %s \n", buffer);
	free(ZCOMMAND);
	free(buffer);
	buffer = NULL;
	ZCOMMAND = NULL;
	usleep(31250);
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

	Send_Command(&fd, &(*ZCOMMAND), &(*buffer), 3);
	printf("Numero de bytes lidos de extended: %ld \n", read(fd, extended, BUFFSIZE * sizeof(char)));

	printf("Valor recebido: %s \n", buffer);
	printf("Valor extendido: %s \n", extended);

	free(ZCOMMAND);
	free(buffer);
	ZCOMMAND = NULL;
	buffer = NULL;
	usleep(31250);
}

void Issue_Command(struct ZSTAR3 *usb_dev)
{
	int command_length;
	int fd = get_fd (&usb_dev->usbstick);
	char *ZCOMMAND, *buffer;
	buffer = malloc (BUFFSIZE * sizeof(char));
	init_buffer(&(*buffer));

	printf("Digite o tamanho em bytes do comando desejado: ");
	scanf("%d", &command_length);
	ZCOMMAND = malloc (command_length * sizeof(char));
	printf("Digite os caracteres do comando, um seguido do outro (sem enter), sem espaçamento: ");
	scanf("%s", ZCOMMAND);

	Send_Command(&fd, &(*ZCOMMAND), &(*buffer), command_length);
	
	printf("Valor armazenado em buffer: %s \n", buffer);

	Asynchronous_read(&fd, &(*buffer));

	free(ZCOMMAND);
	free(buffer);
	ZCOMMAND = NULL;
	buffer = NULL;
}

int Asynchronous_read(int *fd, char *buffer)
{	
	//init_buffer(&(*buffer));
	int FD = *fd;
	int flag = 0;
	//tcflush(FD, TCIOFLUSH);
	do {
		flag = read(FD, buffer, BUFFSIZE * sizeof(char));
		if (flag != 0) {
		printf("Numero de bytes lidos de buffer: %d \n", flag);
		printf("Valor armazenado em buffer: %s \n", buffer);
		}
	} while(flag != 0);

	if (flag <= 0)
		return 0;
	else
		return 1;
}

void Send_Command(int *fd, char *ZCOMMAND, char *buffer, int length)
{
	int FD = *fd;
	int count, i, recebido = 0;
	tcflush(FD, TCIOFLUSH);
	write(FD, ZCOMMAND, length * sizeof(char));
	tcdrain(FD);
	
	while (recebido == 0) {
		
		count = read(FD, buffer, BUFFSIZE * sizeof(char));
		printf("Numero de bytes lidos de buffer: %d \n", count);
		i++;
		
		if (count != 0) {
			recebido = 1;
		}

		if (count == 0 && i == 2) {
			write(FD, ZCOMMAND, length * sizeof(char));
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

	Send_Command(&fd, &(*ZCOMMAND), &(*buffer), 2);
	printf("Buffer lido: %s \n",buffer);

	free(ZCOMMAND);
	free(buffer);
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
	buffer = malloc (BUFFSIZE * sizeof(char) );
	init_buffer(&(*buffer));
	ZCOMMAND[0] = 0x56;
	
	//printf("get_fd(usb_dev.usbstick):%d)\n", get_fd(usb_dev.usbstick));
	gettimeofday(&t1, NULL);
	Send_Command(&fd, &(*ZCOMMAND), &(*buffer), 1);
	gettimeofday(&t2, NULL);
	delta_t = t2.tv_usec - t1.tv_usec;	

	/*Medindo o tempo que leva entre a escrita/tx
	* e a recepção / leitura dos dados */
	printf("Tempo tx/rx: %f \n", delta_t);

	usb_dev->parameters.Acc_x = (double) buffer[1] /21.33;
	usb_dev->parameters.Acc_y = (double) buffer[3] /21.33;
	usb_dev->parameters.Acc_z = (double) buffer[5] /21.33;

	printf("Valor de aceleracao em x[0]: %f \n", usb_dev->parameters.Acc_x);
	printf("Valor de aceleracao em y[0]: %f \n", usb_dev->parameters.Acc_y);
	printf("Valor de aceleracao em z[0]: %f \n", usb_dev->parameters.Acc_z);
	
	if (Asynchronous_read(&fd, &(*buffer))) {

	usb_dev->parameters.Acc_x = (double) buffer[1] /21.33;
	usb_dev->parameters.Acc_y = (double) buffer[3] /21.33;
	usb_dev->parameters.Acc_z = (double) buffer[5] /21.33;

	printf("Valor de aceleracao em x[1]: %f \n", usb_dev->parameters.Acc_x);
	printf("Valor de aceleracao em y[1]: %f \n", usb_dev->parameters.Acc_y);
	printf("Valor de aceleracao em z[1]: %f \n", usb_dev->parameters.Acc_z);
	
	}

	free(buffer);
	free(ZCOMMAND);
	buffer = NULL;
	ZCOMMAND = NULL;
	usleep(31250);
}