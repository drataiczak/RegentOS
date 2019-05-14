#ifndef ITOA_H_
#define ITOA_H_

#define UDEC  99
#define DEC   10
#define HEX   16

char *itoa(int num, char *str, int base);
char *utoa(unsigned int num, char *str);

#endif
