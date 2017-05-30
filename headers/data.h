#ifndef DATA_H
#define DATA_H

/*In the refference manual is said that if the board has
ZSTAR3 protocol, the calibration values are not important */

enum G {
	G8,
	G2,
	G4
};

enum RATE {
	R120,
	R64,
	R32
};

struct data {
	double Acc_x, Acc_y, Acc_z;
	enum G gmode;
	enum RATE tx_rx_rate;
};

#endif