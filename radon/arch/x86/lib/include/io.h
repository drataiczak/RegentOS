#ifndef IO_H_
#define IO_H_

#define TTY_CMD_PORT        0x3D4
#define TTY_DATA_PORT       0x3D5
#define TTY_HIGH_BYTE_CMD   14
#define TTY_LOW_BYTE_CMD    15

void outb(unsigned short port, unsigned char data);

#endif
