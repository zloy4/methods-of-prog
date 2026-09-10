#include <stdio.h>
int get_length(long long num) {
    if (num == 0) return 1;
    int len = 0;
    while (num > 0) {
        len++;
        num /= 10;
    }
    return len;
}

long long power_of_10(int power) {
    long long res = 1;
    for (int i = 0; i < power; i++) {
        res *= 10;
    }
    return res;
}

long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) {
        return x * y;
    }

    int len_x = get_length(x);
    int len_y = get_length(y);
    int md = (len_x > len_y ? len_x : len_y) / 2;

    long long multiplier = power_of_10(md);

    long long levx = x / multiplier;
    long long pravx = x % multiplier; 

    long long levy = y / multiplier;
    long long pravy = y % multiplier;

    long long qw = karatsuba(pravx, pravy);
    long long er = karatsuba(levx, levy);
    long long er_qw = karatsuba(levx + pravx, levy + pravy);

    return qw + (er_qw - er - qw) * multiplier + er * power_of_10(md * 2);
}

int main() {
    long long x = 123;
    long long y = 123;
    
    long long result = karatsuba(x, y);
    printf("Multiplication result: %lld\n", result);
    
    return 0;
}
