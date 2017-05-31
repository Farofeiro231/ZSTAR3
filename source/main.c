#include "../headers/driver.h"
#include "../headers/comunication.h"
#include "../headers/data.h"

int main()
{
	struct ZSTAR3 usbdev;
	init_fd(usbdev.usbstick);
	Handshake_8b(usbdev);
	Rxyz(usbdev);
	close_fd(usbdev.usbstick);
	return 0;
}