
#ifndef _FT232_API_H
#define _FT232_API_H

#define OK 1

int get_number_devices(void);
int open_device(void);
int close_device(void);
int reset_device(void);
int set_baudrate(int);
int set_data_options(void);
int send_data(char *, int);
int send_hello(void);
int read_data_status(void);
int read_data_number(void);
void read_data(void);

#endif