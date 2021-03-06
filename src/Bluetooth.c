#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "Bluetooth.h"

#define Serial_Port "/dev/rfcomm0"
#define Serial_Baud B115200

int uart0_filestream = -1;

void UART() {
    //OPEN THE UART
    uart0_filestream = open(Serial_Port, O_RDWR | O_NOCTTY);
    if (uart0_filestream == -1) {
        //ERROR - CAN'T OPEN SERIAL PORT
        printf("COM - Error - Unable to open UART.  Ensure it is not in use by another application\n");
    }

    //CONFIGURE THE UART
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;        //set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

char * COM_Recv(){
    //Check if the filestream is open
    if(uart0_filestream == -1){
        printf("cannot open the filestream");
        return 0;
    }
    if(tcflush(uart0_filestream, TCIFLUSH)==-1){
        printf("flushing failed");
    }

    char *data_buffer;
    while(1){
        // Read up to 255 characters from the port if they are there
        char rx_buffer[50];

        //Filestream, buffer to store in, number of bytes to read (max)
        int rx_length = read(uart0_filestream, (void *)rx_buffer, 50);
        if (rx_length < 0) {
            //An error occured (will occur if there are no bytes)
            printf("the rx_length is -1, which is not possible");
        }
        else if (rx_length == 0) {
            //No data waiting
            printf("rx_length=0, no data yet");
        }
        else {
            //Bytes received
            rx_buffer[rx_length] = '\0';
            //printf("%i bytes read : %s\n", rx_length, rx_buffer);
            data_buffer=(char*)malloc(sizeof(char)*rx_length+1);
            strcpy(data_buffer,rx_buffer);
            break;
        }
    }
    //printf("I want to return: %s",data_buffer);
    return data_buffer;


}

char * COM_Send(char * Data,int length){
    if (uart0_filestream == -1){
        return "No UART";
    }

    tcflush(uart0_filestream, TCIFLUSH);

    int count = write(uart0_filestream, &Data[0],length);         //Filestream, bytes to write, number of bytes to write
    if (count < 0)
    {
        return "UART TX error\n";
    }else{
        //printf("Count: %i\n",count);
        return "Transmission seems OK\n";
    }
    tcdrain(uart0_filestream);
}

void COM_Close(){
    close(uart0_filestream);
}