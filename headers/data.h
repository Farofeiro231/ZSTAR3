#ifndef DATA_H
#define DATA_H

/*In the refference manual is said that if the board has
*ZSTAR3 protocol, the calibration values are not important */

/* The MMA7660FC supports only +- 1.5 g operation.
* Uncomment the section below if your board has
* extended g-mode support.*/

/*enum G {
	G8,
	G2,
	G4
};*/

/*The accelerometer MMA7660FC is compatible with the
* sampling rates below. Adapt the code to fit the capabilities
* of your board*/

enum RATE {
	R120,
	R64,
	R32,
	R16,
	R8,
	R4,
	R2,
	R1
};

struct data {
	double Acc_x, Acc_y, Acc_z;
	enum RATE tx_rx_rate;
};

#endif