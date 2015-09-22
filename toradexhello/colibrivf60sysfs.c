#include "colibrivf60sysfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>                   // for open(), close(), lseek()
#include <sys/stat.h>                // for open()
#include <sys/types.h>               // for open()
#include <unistd.h>

void exportgpio(char ** _portas,int y){
	int x,retval,fdescrisp;

	for( x=0;x<y;x++){

		fdescrisp=open(PATH_EXPORT,O_WRONLY);
		retval=write(fdescrisp,*_portas ,sizeof(*_portas));
		retval=close(fdescrisp);
		_portas++;
		}
	printf("%d",retval);

}
void unexportgpio(char ** _portas,int y){
	int x,retval,fdescrisp;

	fdescrisp=open(PATH_UNEXPORT,O_WRONLY);
	for(x=0;x<y;x++){
		retval=write(fdescrisp,*_portas ,sizeof(*_portas));
		_portas++;
		}
	retval=close(fdescrisp);
	printf("%d",retval);
}
void configpio(char * _x,char * _y){
	int retval,fdescrisp;

			fdescrisp=open(_x,O_RDWR);
			retval=write(fdescrisp,_y ,sizeof(_y));
			retval=close(fdescrisp);
			printf("%d",retval);

}
