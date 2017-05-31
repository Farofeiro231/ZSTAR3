#include "../headers/driver.h"
#include "../headers/comunication.h"
#include "../headers/data.h"

int main()
{
	//int i = 0;
	struct ZSTAR3 usbdev;
	init_fd(&usbdev.usbstick);
	Set_Data_Rate(&usbdev, 64);
	Get_Data_Rate(&usbdev);
	//Handshake_8b(usbdev);
	/*while(i<100000) {
		Rxyz(&usbdev);
		i=i+1;
		//printf("Valor de i:%d\n",i);
	}*/
	close_fd(&usbdev.usbstick);
	return 0;
}