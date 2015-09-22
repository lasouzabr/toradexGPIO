/*
 * toradexhello.c
 *
 *  Created on: Sep 10, 2015
 *      Author: leonardo
 */

#include "colibrivf60sysfs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>                   // for open(), close(), lseek()
#include <sys/stat.h>                // for open()
#include <sys/types.h>               // for open()
#include <unistd.h>                  // for write(), open(), read(), usleep()


#define LEDS 3
#define KEYS 3

static char *PORTS_KEY[]={"46","88","48"};
static char *PORTS_LED[]={"47","50","53"};

int main(int argc, char *argv[])
{
	int retval,i,x;
	Gpio leds[LEDS],keys[KEYS];
	char p[40]="";


	exportgpio(PORTS_KEY,3);
	exportgpio(PORTS_LED,3);


	/*inicializa Objetos LED e direcao mapeadas em sysfs*/

	for( x=0;x<LEDS;x++){
		leds[x].value=OFF;
		leds[x].direcao=OUT;
		strcat(p,PATH_OBJ);
		strcat(p,PORTS_LED[x]);
		strcat(p,"/value");
		leds[x].v_path=malloc(strlen(p)+1);
		strcpy(leds[x].v_path,p);
		p[0]='\0';
		strcat(p,PATH_OBJ);
		strcat(p,PORTS_LED[x]);
		strcat(p,"/direction");
		leds[x].d_path=malloc(strlen(p)+1);
		strcpy(leds[x].d_path,p);
		configpio(leds[x].d_path,OUT);
		p[0]='\0';
	}

	for( x=0;x<KEYS;x++){
		keys[x].direcao=IN;
		p[0]='\0';
		strcat(p,PATH_OBJ);
		strcat(p,PORTS_KEY[x]);
		strcat(p,"/value");
		keys[x].v_path=malloc(strlen(p)+1);
		strcpy(keys[x].v_path,p);
		p[0]='\0';
		strcat(p,PATH_OBJ);
		strcat(p,PORTS_KEY[x]);
		strcat(p,"/direction");
		keys[x].d_path=malloc(strlen(p)+1);
		strcpy(keys[x].d_path,p);
		configpio(keys[x].d_path,IN);


	}

	/* Abrir descritors LED*/
	for(i=0;i<LEDS;i++)
		leds[i].FD= open(leds[i].v_path,O_WRONLY);
	/* Abrir descritors KEYS*/
	for(i=0;i<KEYS;i++)
		keys[i].FD= open(keys[i].v_path,O_RDONLY);



/* 20 segundos pisca leds*/
	x=0;
	do
	{
		for(i=0;i<LEDS;i++){
		leds[i].value=(leds[i].value==ON)?OFF:ON;
		retval = write(leds[i].FD, &leds[i].value, sizeof(leds[i].value));
		}
		usleep(500000);
		x++;
	}while(x<10);



/* 10 segundos le chaves*/
	x=0;
	do
		{
			for(i=0;i<3;i++){

			retval = read(keys[i].FD, &keys[i].value, sizeof(keys[i].value));
			lseek(keys[i].FD,0,SEEK_SET);
			leds[i].value=(keys[i].value==ON)?OFF:ON;
			retval = write(leds[i].FD, &leds[i].value, sizeof(leds[i].value));
			}
			usleep(100000);

			x++;
		}while(x<100);

	/*fechar descritores de arquivo LEDS*/
	for(x=0;x<LEDS;x++)
		retval=close(leds[x].FD);
	/*fechar descritores de arquivo KEYS*/
	for(x=0;x<KEYS;x++)
		retval=close(keys[x].FD);


	unexportgpio(PORTS_KEY,3);
	unexportgpio(PORTS_LED,3);

	printf("Teste arm compiler toradex:%d \n",retval);

		return(0);

}
