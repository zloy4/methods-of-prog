#include <stdio.h>

unsigned long long karatsuba(unsigned long long x,
                             unsigned long long y)
{
    unsigned long long a1, a0;
    unsigned long long b1, b0;
    unsigned long long p1, p2, p3;
    unsigned long long middle;
    unsigned long long power;
    int n = 0;
    int m;

    if (x < 10 || y < 10)
    {
        return x * y;
    }

    unsigned long long temp = x;

    while (temp > 0)
    {
        n++;
        temp /= 10;
    }

    if (n % 2 != 0)
    {
        n++;
    }

    m = n / 2;

    power = 1;

    for (int i = 0; i < m; i++)
    {
        power *= 10;
    }

    a1 = x / power;
    a0 = x % power;

    b1 = y / power;
    b0 = y % power;

    p1 = karatsuba(a1, b1);
    p2 = karatsuba(a0, b0);

    p3 = karatsuba(a1 + a0, b1 + b0);

    middle = p3 - p1 - p2;

    return p1 * power * power
           + middle * power
           + p2;
}

int main(void)
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long result;

    printf("Введите первое число: ");
    scanf("%llu", &a);

    printf("Введите второе число: ");
    scanf("%llu", &b);

    result = karatsuba(a, b);

    printf("Результат: %llu\n", result);

    return 0;
}
