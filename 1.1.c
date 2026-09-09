#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10000

typedef struct {
    int *digits;
    int size;
} BigNumber;

BigNumber to_digits(const char *number) {
    BigNumber result;

    int length = strlen(number);
    result.size = (length + 3) / 4;
    result.digits = calloc(result.size, sizeof(int));

    int index = 0;

    for (int i = length; i > 0; i -= 4) {
        int start = i - 4;

        if (start < 0) {
            start = 0;
        }

        int block = 0;

        for (int j = start; j < i; j++) {
            block = block * 10 + (number[j] - '0');
        }

        result.digits[index] = block;
        index++;
    }

    return result;
}

void free_number(BigNumber number) {
    free(number.digits);
}

void print_number(BigNumber number) {
    int i = number.size - 1;

    printf("%d", number.digits[i]);

    for (i--; i >= 0; i--) {
        printf("%04d", number.digits[i]);
    }

    printf("\n");
}

BigNumber multiply(BigNumber a, BigNumber b) {
    BigNumber result;

    result.size = a.size + b.size;
    result.digits = calloc(result.size, sizeof(int));

    for (int i = 0; i < a.size; i++) {
        for (int j = 0; j < b.size; j++) {
            result.digits[i + j] += a.digits[i] * b.digits[j];
        }
    }

    for (int i = 0; i < result.size - 1; i++) {
        int carry = result.digits[i] / BASE;

        result.digits[i] %= BASE;
        result.digits[i + 1] += carry;
    }

    while (result.size > 1 &&
           result.digits[result.size - 1] == 0) {
        result.size--;
    }

    return result;
}


int main() {
    char a[10000];
    char b[10000];

    printf("Введите первое число: ");
    scanf("%9999s", a);

    printf("Введите второе число: ");
    scanf("%9999s", b);

    BigNumber x = to_digits(a);
    BigNumber y = to_digits(b);

    BigNumber result = multiply(x, y);

    printf("Результат: ");
    print_number(result);

    free_number(x);
    free_number(y);
    free_number(result);

    return 0;
}
