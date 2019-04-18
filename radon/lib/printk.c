#include <printk.h>
#include <limits.h> /* INT_MAX */
#include <string.h>
#include <stdarg.h> /* va_* */
#include <tty.h>
#include <stdlib.h> /* itoa() */
#include <ctype.h> /* to_upper()/to_lower() */

static int print(const char *data, size_t len) {
    const unsigned char *bytes = (const unsigned char *)data;
    size_t i;

    for(i = 0; i < len; i++) {
        if(bytes[i]) {
            tty_putc(bytes[i]);
        }
        else {
            break;
        }
    }

    return i;
}

int printk(const char *restrict fmt, ...) {
    va_list params;
    int written = 0;
    int base = 0;
    int is_upper = 0;
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
            case 'd':
                base = DEC;
                /* Fallthrough */

            case 'X':
                DEC == base ? (is_upper = 0) : (is_upper = 1);
                /* Fallthrough */

            case 'x':
                fmt++;
                int v = va_arg(params, int);
                char b[100];
                base = base > 0 ? base : HEX;
               
                itoa(v, b, base);

                if(is_upper) {
                    for(int j = 0; j < 100; j++) {
                        b[j] = to_upper(b[j]);
                    }
                }
                else {
                    for(int j = 0; j < 100; j++) {
                        b[j] = to_lower(b[j]);
                    }
                }

                written += print(b, 100);

                break;

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
