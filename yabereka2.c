#include "main.h"
#include <unistd.h>

int p_uch(va_list a, char b[], int f, int w, int p, int s) {
    char c = va_arg(a, int);
    return (h_w_uch(c, b, f, w, p, s));
}

int p_str(va_list a, char b[], int f, int w, int p, int s) {
    int l = 0, i;
    char *str = va_arg(a, char *);

    UNUSED(b);
    UNUSED(f);
    UNUSED(w);
    UNUSED(p);
    UNUSED(s);
    
    if (str == NULL) {
        str = "(null)";
        if (p >= 6)
            str = "      ";
    }

    while (str[l] != '\0')
        l++;

    if (p >= 0 && p < l)
        l = p;

    if (w > l) {
        if (f & F_MINUS) {
            write(1, &str[0], l);
            for (i = w - l; i > 0; i--)
                write(1, " ", 1);
            return (w);
        }
        else {
            for (i = w - l; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], l);
            return (w);
        }
    }

    return (write(1, str, l));
}

int p_pct(va_list a, char b[], int f, int w, int p, int s) {
    UNUSED(a);
    UNUSED(b);
    UNUSED(f);
    UNUSED(w);
    UNUSED(p);
    UNUSED(s);
    return (write(1, "%%", 1));
}

int p_int(va_list a, char b[], int f, int w, int p, int s) {
    int i = BUFF_SIZE - 2;
    int ngtv = 0;
    long int n = va_arg(a, long int);
    unsigned long int num;

    n = c_s_u(n, s);

    if (n == 0)
        b[i--] = '0';

    b[BUFF_SIZE - 1] = '\0';
    num = (unsigned long int)n;

    if (n < 0) {
        num = (unsigned long int)((-1) * n);
        ngtv = 1;
    }

    while (num > 0) {
        b[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_u(ngtv, i, b, f, w, p, s));
}

int p_bin(va_list a, char b[], int f, int w, int p, int s) {
    unsigned int n, m, i, sum;
    unsigned int arr[32];
    int cnt;

    UNUSED(b);
    UNUSED(f);
    UNUSED(w);
    UNUSED(p);
    UNUSED(s);

    n = va_arg(a, unsigned int);
    m = 2147483648;
    arr[0] = n / m;
    for (i = 1; i < 32; i++) {
        m /= 2;
        arr[i] = (n / m) % 2;
    }
    for (i = 0, sum = 0, cnt = 0; i < 32; i++) {
        sum += arr[i];
        if (sum || i == 31) {
            char z = '0' + arr[i];
            write(1, &z, 1);
            cnt++;
        }
    }
    return (cnt);
}
