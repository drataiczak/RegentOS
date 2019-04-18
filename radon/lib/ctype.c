#include <ctype.h>

int to_upper(int ch) {
    /* Check if between a and z */
    return (ch >= 0x61 && ch <= 0x7A) ? ch - 0x20 : ch;    
}

int to_lower(int ch) {
    /* Check if between A and Z */
    return (ch >= 0x41 && ch <= 0x5A) ? ch + 0x20 : ch;
}
