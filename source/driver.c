#include "driver.h"

void init_fd(struct port_device usbstick)
{
	/*
	O_NOCTTY - O processo não quer ser o "controlador" para a porta. Caso contrário, ctrl + c poderia afetar o processo (p.e.)
	*/
	usbstick.fd = open(USBDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (usbstick.fd == -1)
		perror("Could not open device on port ACM0!\n");
	else  {
		fcntl(usbstick.fd, F_SETFL, FNDELAY);	//Retorna o estado de "bloqueio" e espera por dados do descritor
		printf("Comunicacao iniciada com sucesso!\n");
		config_fd(usbstick);
	}
}

void config_fd(struct port_device usbstick)
{
	printf("Valor de usbstick.fd: %d\n", usbstick.fd);
	struct termios options;
	/*
	* Get the current options for the port...
 	*/

	memset (&options, 0, sizeof(options));

	tcgetattr(usbstick.fd, &options);

	/*Configure input and output baudrates*/

	/*Não sei ainda quantos bytes são enviados/recebidos*/

	cfsetispeed(&options, B19200);
	cfsetospeed(&options, B19200);

	/*Configuring the flags for communication*/
	/*Removing parity and stop bits, as well as setting 8 bits per byte and removing character size mask*/

	options.c_cflag &= ~( PARENB | PARODD);
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag |= (CLOCAL | CREAD);	//Normal mode and enable receiving bytes
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 	//Allow program to read raw data input

	options.c_cc[VMIN]  = 0;            // read doesn't block
        	options.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        	tcflush(usbstick.fd, TCIFLUSH );
	tcsetattr(usbstick.fd, TCSANOW, &options); 	//Change fd parameters without waiting to finish tx or rx.
}

int get_fd(struct port_device usbstick)
{
	return usbstick.fd;
}

void close_fd(struct port_device usbstick)
{
	close(usbstick.fd);
}