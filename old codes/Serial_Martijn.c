#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define Serial_Port "/dev/rfcomm0"
#define Serial_Baud B115200

void * UART(){

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
    //options.c_cflag = B38400 | CS8 | CLOCAL | CREAD;         //<Set baud rate
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;        //set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    char data[50];
    memset(data,0,50);

    while(!stop){
        if(COM_Recv(data)){
            COM_Parse(data);
            memset(data,0,50);
        }
        usleep(1000);
    }

    //----- CLOSE THE UART -----
    close(uart0_filestream);
}

char * COM_Send(char * Data,int length){
    if (uart0_filestream == -1){
        return "No UART";
    }

    tcflush(uart0_filestream, TCIFLUSH);

    int count = write(uart0_filestream, &data[0],length);         //Filestream, bytes to write, number of bytes to write
    if (count < 0)
    {
        printf("UART TX error\n");
    }else{
        //printf("Count: %i\n",count);
    }
    tcdrain(uart0_filestream);
}

int COM_Recv(char * OUT_Data){
    //Check if the filestream is open
    if(uart0_filestream == -1){
        return 0;
    }
    int index = 0;

    //Create buffer and clear it
    unsigned char data_buffer[256] = {};
    memset(data_buffer,0,256);
    while(1){
        // Read up to 255 characters from the port if they are there
        unsigned char rx_buffer[255];

        //Filestream, buffer to store in, number of bytes to read (max)
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);
        if (rx_length < 0)
        {
            //An error occured (will occur if there are no bytes)
        }
        else if (rx_length == 0)
        {
            //No data waiting
        }
        /*else if (rx_length == 8)
        {
            rx_buffer[rx_length] = '\0';
            //printf("%i bytes read : %s\n", rx_length, rx_buffer);
            for(int i = 0;i<8;i++){
                data_buffer[index++] = rx_buffer[i];
            }
        }*/
        else
        {
            //Bytes received
            rx_buffer[rx_length] = '\0';
            //printf("%i bytes read : %s\n", rx_length, rx_buffer);
            for(int i = 0;i<rx_length;i++){
                data_buffer[index++] = rx_buffer[i];
            }
            break;
        }
        return index;
    }

    for(int i = 0;i<index;i++){
        OUT_Data[i] = data_buffer[i];
    }
}

