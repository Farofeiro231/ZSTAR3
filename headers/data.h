#ifndef DATA_H
#define DATA_H

/*In the refference manual is said that if the board has
ZSTAR3 protocol, the calibration values are not important */

enum g{
/*Criar conteúdos do enum*/
}

enum rate{
/*Criar conteúdos do enum*/
}

struct data{
	double Acc_x, Acc_y, Acc_z;
	enum g gmode;
	enum rate tx_rx_rate;
}

#endif