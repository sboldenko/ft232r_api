
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include "../headers/ftd2xx.h"
#include "../headers/ft232_api.h"

int get_number_devices(void);
int open_device(void);
int reset_device(void);
int close_device(void);
int set_baudrate(int);
int set_data_options(void);
int send_data(char *, int);
int send_hello(void);
int read_data_status(void);
int read_data_number(void);
void read_data(void);

int main(void)
{
    int number_devices;
    int device_status;
    int read_status;
    int number_read_data;
    int i;

    char *TxBuffer = "I am API!\r\n";
    char RxBuffer[256];

    number_devices = get_number_devices();
    printf("Number FTDI devices = %d\n", number_devices);

    device_status = open_device();
    if (device_status == OK)
        printf("FTDI device opened.\n");
    else
        printf("FTDI device not opened.\n");

    device_status = reset_device();
    if (device_status == OK)
        printf("Device is reset.\n");
    else
        printf("Device is not reseted.\n");

    device_status = set_baudrate(9600);
    if (device_status == OK)
        printf("Baudrate is 9600.\n");
    else
        printf("Baudrate is failed.\n");

    device_status = set_data_options();
    if (device_status == OK)
    {
        printf("Data options:\n");
        printf(" Data bits - 8.\n");
        printf(" Stop bits - 1.\n");
        printf(" Parity - none.\n");
    }
    else
        printf("Data options is failed.\n");

    device_status = send_hello();
    if (device_status == OK)
        printf("Hello send.\n");
    else
        printf("Hello not send.\n");

    device_status = send_data(TxBuffer, 11);
    if (device_status == OK)
        printf("Data send.\n");
    else
        printf("Data not send.\n");

    while(read_status != OK)
    {
        read_status = read_data_status();
    }

    number_read_data = read_data_number();
    printf("Data number=%d\n", number_read_data);

    read_data();
/*
    for (i = 0; i < number_read_data; i++)
    {
        RxBuffer[i] = read_data(i);
        printf("Data[%d]=%c\n", i, RxBuffer[i]);
    }
*/
/*
    device_status = close_device();
    if (device_status == OK)
        printf("FTDI device closed.\n");
    else
        printf("FTDI device not closed.\n");
*/

    getchar();
    return 0;
}