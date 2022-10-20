#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include "../headers/ftd2xx.h"
#include "../headers/ft232_api.h"

FT_HANDLE ftHandle;

int get_number_devices(void)
{
    FT_STATUS ftStatus;
    DWORD numDevs;

    ftStatus = FT_CreateDeviceInfoList(&numDevs);

    if (ftStatus == FT_OK)
        return numDevs;
    else
        return -1;
}

int open_device(void)
{
    FT_STATUS ftStatus;

    ftStatus = FT_OpenEx("VE00000000", FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;
}

int close_device(void)
{
    FT_STATUS ftStatus;

    ftStatus = FT_Close(ftHandle);

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;
}

int reset_device(void)
{
    FT_STATUS ftStatus;

    ftStatus = FT_ResetDevice(ftHandle);

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;
}

int set_baudrate(int baudrate)
{
    FT_STATUS ftStatus;

    ftStatus = FT_SetBaudRate(ftHandle, baudrate);

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;
}

int set_data_options(void)
{
    FT_STATUS ftStatus;

    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;
}

int send_data(char * data, int length)
{
    FT_STATUS ftStatus;
    DWORD BytesWritten;

    ftStatus = FT_Write(ftHandle, data, length, &BytesWritten);

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;
}

int send_hello(void)
{
    FT_STATUS ftStatus;
    DWORD BytesWritten;

    char *TxBuffer = "Hello World!\r\n";

    ftStatus = FT_Write(ftHandle, TxBuffer, 14, &BytesWritten);

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;
}

int read_data_status(void)
{
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;

    FT_SetTimeouts(ftHandle, 5000, 0);
    FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);

    if (RxBytes > 0)
    {
        printf("Read buffer is not empty.\n");
        printf("TxBytes = %d.\n", TxBytes);
        printf("RxBytes = %d.\n", RxBytes);
        return 1;
    }
    else
        return -1;
}

int read_data_number(void)
{
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;

    FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);

    return RxBytes;
}

void read_data(void)
{
    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    char RxBuffer[128];

    FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);

    ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);

    printf("BytesReceived = %d\n", BytesReceived);

    int i;

    for (i = 0; i < RxBytes; i++)
    {
        printf("Data[%d]=%c\n", i, RxBuffer[i]);
    }

    if (ftStatus == FT_OK)
        return 1;
    else
        return -1;

}