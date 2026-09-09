#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846


void fft(double complex *a, int n, int invert)
{
    int i;
    int j = 0;

    for (i = 1; i < n; i++)
    {
        int bit = n >> 1;

        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }

        j ^= bit;

        if (i < j)
        {
            double complex temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    for (int length = 2; length <= n; length *= 2)
    {
        double angle = 2.0 * PI / length;

        if (invert)
        {
            angle = -angle;
        }

        double complex w_length =
            cos(angle) + I * sin(angle);

        for (i = 0; i < n; i += length)
        {
            double complex w = 1.0 + 0.0 * I;

            for (j = 0; j < length / 2; j++)
            {
                double complex u = a[i + j];
                double complex v =
                    a[i + j + length / 2] * w;

                a[i + j] = u + v;
                a[i + j + length / 2] = u - v;

                w *= w_length;
            }
        }
    }

    if (invert)
    {
        for (i = 0; i < n; i++)
        {
            a[i] /= n;
        }
    }
}


void print_array(double complex *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%.2f + %.2fi\n",
               creal(a[i]),
               cimag(a[i]));
    }
}


void multiply_fft(const char *number1,
                  const char *number2)
{
    int len1 = 0;
    int len2 = 0;

    while (number1[len1] != '\0')
    {
        len1++;
    }

    while (number2[len2] != '\0')
    {
        len2++;
    }

    int n = 1;

    while (n < len1 + len2)
    {
        n *= 2;
    }

    double complex *a =
        calloc(n, sizeof(double complex));

    double complex *b =
        calloc(n, sizeof(double complex));

    if (a == NULL || b == NULL)
    {
        printf("Ошибка выделения памяти\n");
        free(a);
        free(b);
        return;
    }

    for (int i = 0; i < len1; i++)
    {
        a[i] = number1[len1 - 1 - i] - '0';
    }

    for (int i = 0; i < len2; i++)
    {
        b[i] = number2[len2 - 1 - i] - '0';
    }

    fft(a, n, 0);
    fft(b, n, 0);

    for (int i = 0; i < n; i++)
    {
        a[i] *= b[i];
    }

    fft(a, n, 1);

    long long *result =
        calloc(n + 1, sizeof(long long));

    if (result == NULL)
    {
        printf("Ошибка выделения памяти\n");
        free(a);
        free(b);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        result[i] = llround(creal(a[i]));
    }

    for (int i = 0; i < n; i++)
    {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    int last = n;

    while (last > 0 && result[last] == 0)
    {
        last--;
    }

    printf("Результат: ");

    for (int i = last; i >= 0; i--)
    {
        printf("%lld", result[i]);
    }

    printf("\n");

    free(a);
    free(b);
    free(result);
}


int main(void)
{
    char number1[1000];
    char number2[1000];

    printf("Введите первое число: ");
    scanf("%999s", number1);

    printf("Введите второе число: ");
    scanf("%999s", number2);

    multiply_fft(number1, number2);

    return 0;
}
