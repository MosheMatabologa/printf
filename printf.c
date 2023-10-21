#include "main.h"
#include <unistd.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int chars_printed = 0;

    while (*format) {
        if (*format == '%') {
            format++; // Move past '%'
            if (*format == 'c') {
                int c = va_arg(args, int);
                write(1, &c, 1); // Write the character to stdout
                chars_printed++;
            } else if (*format == 's') {
                const char *str = va_arg(args, const char *);
                while (*str) {
                    write(1, str, 1); // Write each character of the string to stdout
                    str++;
                    chars_printed++;
                }
            } else if (*format == '%') {
                write(1, "%", 1); // Write '%' to stdout
                chars_printed++;
            }
        } else {
            write(1, format, 1); // Write the character to stdout
            chars_printed++;
        }
        format++;
    }

    va_end(args);
    return chars_printed;
}

