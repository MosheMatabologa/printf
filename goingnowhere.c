#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int chars_printed = 0;

    while (*format) {
        if (*format == '%') {
            format++; // Move past '%'
            if (*format == 'c') {
                int c = va_arg(args, int);
                putchar(c);
                chars_printed++;
            } else if (*format == 's') {
                const char *str = va_arg(args, const char *);
                while (*str) {
                    putchar(*str);
                    str++;
                    chars_printed++;
                }
            } else if (*format == '%') {
                putchar('%');
                chars_printed++;
            }
        } else {
            putchar(*format);
            chars_printed++;
        }
        format++;
    }

    va_end(args);
    return chars_printed;
}

int main() {
    int num_chars = _printf("Hello, %s! My favorite character is %c. This is a %% sign: %%\n", "World", 'A');
    printf("\nNumber of characters printed: %d\n", num_chars);
    return 0;
}
