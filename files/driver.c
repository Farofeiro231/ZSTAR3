#include "driver.h"

int port_device::init_fd(void)
{
	int fd; /*File descriptor para a porta serial*/
	
	/*
	O_NOCTTY - O processo não quer ser o "controlador" para a porta. Caso contrário, ctrl + c poderia afetar o processo (p.e.)
	*/
	
	fd = open(USBDEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1){
		perror("Could not open device on port %s", USBDEVICE"!\n");
	} else fcntl(fd, F_SETFL, 0);	//Retorna o estado de "bloqueio" e espera por dados do descritor

	return (fd);
}

int port_device::config_fd(void)
{
	
	struct termios options;
	/*
	* Get the current options for the port...
 	*/
 	
	tcgetattr(fd, &options);

	/*Configure input and output baudrates*/

	/*Não sei ainda quantos bytes são enviados/recebidos*/

	cfsetispeed(&options, B19200);
	cfsetospeed(&options, B19200);

	/*Configuring the flags for communication*/
	/*Removing parity and stop bits, as well as setting 8 bits per byte and removing character size mask*/

	options.c_cflag &= ~PARENB
	options.c_cflag &= ~CSTOPB
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag |= (CLOCAL | CREAD)	//Normal mode and enable receiving bytes
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 	//Allow program to read raw data input

	tcsetattr(fd, TCSANOW, &options) 	//Change fd parameters without waiting to finish tx or rx.
	return 0;
}

int port_device::get_fd(void)
{
	return fd;
}

void port_device::close_fd(void)
{
	close(fd);
}