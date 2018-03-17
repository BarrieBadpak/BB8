#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bluetooth.h"

int main(void){
    UART();

    char dataToSend[50];
    printf("Input your data to send over bluetooth serial connection:\n");
    scanf("%[^\n]s",dataToSend);

    char * returnMessage = COM_Send(dataToSend,strlen(dataToSend));
    printf("The returned message is: %s\n",returnMessage);

    COM_Close;
}
