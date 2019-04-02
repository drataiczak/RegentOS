#include <string.h>

size_t strlen(const char *str) {
    size_t len = 0;

    while(str[len]) {
        len++;
    }

    return len;
}

size_t strnlen(const char *str, size_t len) {
    size_t count = 0;

    while(str[len] && count < len) {
        count++;
    }

    return count;
}
