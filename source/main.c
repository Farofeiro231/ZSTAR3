#include "../headers/driver.h"
#include "../headers/comunication.h"
#include "../headers/data.h"

int main(int argc, char *argv[])
{
	struct ZSTAR3 usbdev;
	init_fd(&usbdev.usbstick);
	//int rate;
	//scanf("%d", &rate);
	//int i = 0;
	//Change_Focus(&usbdev);
	//Get_Data_Rate(&usbdev);
	//Set_Data_Rate(&usbdev, rate);
	Read_register(&usbdev);
	//Get_Data_Rate(&usbdev);
	/*while(i<100000) {
		Rxyz(&usbdev);
		i=i+1;
		printf("Valor de i:%d\n",i);
	}*/
	close_fd(&usbdev.usbstick);
	return 0;
}