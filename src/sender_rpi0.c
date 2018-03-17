#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdarg.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <termios.h>
#include "Bluetooth.h"

//#define Serial_Port "/dev/rfcomm0"
//#define Serial_Baud B115200

//int uart0_filestream = -1;

/*
void UART(){

    //OPEN THE UART
    uart0_filestream = open(Serial_Port, O_RDWR | O_NOCTTY);
    if (uart0_filestream == -1)
    {
        //ERROR - CAN'T OPEN SERIAL PORT
        printf("COM - Error - Unable to open UART.  Ensure it is not in use by another application\n");
    }

    //CONFIGURE THE UART
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    //options.c_cflag = B38400 | CS8 | CLOCAL | CREAD;         //Set baud rate
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;        //set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    /*char data[50];
    memset(data,0,50);

    while(!stop){
        if(COM_Recv(data)){
            COM_Parse(data);
            memset(data,0,50);
        }
        usleep(1000);
    }

    //----- CLOSE THE UART -----
    //close(uart0_filestream);
}


char * COM_Send(char * Data,int length){
    if (uart0_filestream == -1){
        return "No UART";
    }

    tcflush(uart0_filestream, TCIFLUSH);

    int count = write(uart0_filestream, &data[0],length);         //Filestream, bytes to write, number of bytes to write
    if (count < 0)
    {
        return "UART TX error\n";
    }else{
        //printf("Count: %i\n",count);
        return "Transmission seems OK\n";
    }
    tcdrain(uart0_filestream);
}
*/

int main(void){
    UART();

    char dataToSend[50];
    printf("Input your data to send over bluetooth serial connection:\n");
    scanf("%[^\n]s",dataToSend);

    char * returnMessage = COM_Send(dataToSend,strlen(dataToSend));
    printf("The returned message is: %s\n",returnMessage);

    COM_Close;
}