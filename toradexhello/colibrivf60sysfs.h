/*
 * colibrivf60sysfs.h
 *
 *  Created on: Sep 18, 2015
 *      Author: leonardo
 */

#ifndef COLIBRIVF60SYSFS_H_
#define COLIBRIVF60SYSFS_H_



#define IN "in"
#define OUT "out"
#define ON '1'
#define OFF '0'
#define PATH_OBJ "/sys/class/gpio/gpio"
#define PATH_EXPORT "/sys/class/gpio/export"
#define PATH_UNEXPORT "/sys/class/gpio/unexport"

typedef struct {
			char  value;
			char *direcao;
			char *v_path;
			char *d_path;
			int FD;
			}Gpio;

		void exportgpio(char ** _portas, int y);
		void unexportgpio(char ** _portas, int y);
		void configpio(char * _x,char * _y);

#endif /* COLIBRIVF60SYSFS_H_ */
