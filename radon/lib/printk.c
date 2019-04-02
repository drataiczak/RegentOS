#include <printk.h>
#include <limits.h> /* INT_MAX */
#include <string.h>
#include <stdarg.h> /* va_* */
#include <tty.h>

static int print(const char *data, size_t len) {
    const unsigned char *bytes = (const unsigned char *)data;
    size_t i;

    for(i = 0; i < len; i++) {
        /* TODO Deal with possibility of failure */
        tty_putc(bytes[i]);
    }

    return 1;
}

int printk(const char *restrict fmt, ...) {
    va_list params;
    int written = 0;
    const char *fmt_begin_at;

    va_start(params, fmt);

    while('\0' != *fmt) {
        size_t max_remaining = INT_MAX - written;
        size_t amt;

        if('%' != fmt[0] || '%' == fmt[1]) {
            if('%' == fmt[0]) {
                fmt++;
            }

            amt = 1;
            while(fmt[amt] && '%' != fmt[amt]) {
                amt++;
            }

            if(max_remaining < amt) {
                /* TODO EOVERFLOW */
                return -1;
            }

            if(0 == print(fmt, amt)) {
                return -1;
            }

            fmt += amt;
            written += amt;

            continue;
        }

        fmt_begin_at = fmt++;

        switch(*fmt) {
            case 'c':
                    fmt++;
                    char c = (char)va_arg(params, int);

                    if(!max_remaining) {
                        /* TODO EOVERFLOW */
                        return -1;
                    }

                    if(0 == print(&c, sizeof(c))) {
                        return -1;
                    }

                    written++;

                    break;

            case 's':
                    fmt++;
                    const char *str = va_arg(params, const char *);
                    size_t len = strlen(str);

                    if(max_remaining < len) {
                        /* TODO EOVERFLOW */
                        return -1;
                    }

                    if(0 == print(str, len)) {
                        return -1;
                    }

                    written += len;

                    break;

            case 'd':
                    /* TODO implement */
                    return 0;
            case 'x':
                    /* TODO implemnt */
                    return 0;
            default:
                fmt = fmt_begin_at;
                size_t sz = strlen(fmt);

                if(max_remaining < sz) {
                    /* TODO EOVERFLOW */
                    return -1;
                }

                written += len;
                fmt += len;
        }
    }

    va_end(params);

    return written;
}
