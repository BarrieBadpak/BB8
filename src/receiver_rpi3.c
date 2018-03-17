#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bluetooth.h"

int main(void){
    UART();
    printf("Opened COMM, ready to receive data? (y/n)");
    char cmd;
    while(1){
	scanf("%c", &cmd);
	    if(cmd == 'y'){
	        break;
	    }
    }
    char * receivedData = COM_Recv();

    printf("The received data is: %s\n",receivedData);

    COM_Close;

}
