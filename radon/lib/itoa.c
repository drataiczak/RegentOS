#include <itoa.h>
#include <stdio.h>

void _reverse(char *buf, int len) {
    /* Make sure to account for the null byte at the end */
    char *begin = buf;
    char *end = buf + (len - 1);

    while(begin < end) {
        char temp = *begin;
        *begin = *end;
        *end = temp;

        begin++;
        end--;
    }
}

/* Change this to include other bases (hex, octal, etc) */
char *itoa(int num, char *str, int base) {
    int i = 0;
    int is_neg = 0;

    if(0 == num) {
        str[i++] = '0';
        str[i] = '\0';
        
        return str;
    }

    if(num < 0 && DEC == base) {
        is_neg = 1;
        num = ~num + 1;
    }

    while(0 != num) {
        int remainder = num % base;

        str[i++] = remainder > 9 ? (remainder - 10) + 'a' : remainder + '0';
        num /= base;
    }

    if(is_neg) {
        str[i++] = '-';
    }

    str[i] = '\0';
    _reverse(str, i);
    
    /* Properly handle other numbers (duh) */
    return str;
}

char *utoa(unsigned int num, char *str) {
    int i = 0;

    if(0 == num) {
        str[i++] = '0';
        str[i] = '\0';

        return str;
    }

    while(0 != num) {
        int remainder = num % DEC;
       
        str[i++] = remainder + '0';
        num /= DEC;
    }

    str[i] = '\0';
    _reverse(str, i);

    return str;
}
