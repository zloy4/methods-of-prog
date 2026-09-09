import cmath
import math


def fft(a, invert=False):
    n = len(a)

    j = 0

    for i in range(1, n):
        bit = n >> 1

        while j & bit:
            j ^= bit
            bit >>= 1

        j ^= bit

        if i < j:
            a[i], a[j] = a[j], a[i]

    length = 2

    while length <= n:
        angle = 2 * math.pi / length

        if invert:
            angle = -angle

        w_length = cmath.exp(1j * angle)

        for i in range(0, n, length):
            w = 1

            for j in range(i, i + length // 2):
                u = a[j]
                v = a[j + length // 2] * w

                a[j] = u + v
                a[j + length // 2] = u - v

                w *= w_length

        length *= 2

    if invert:
        for i in range(n):
            a[i] /= n

    return a


def main():
    n = int(input("Введите размер массива: "))

    a = []

    for i in range(n):
        value = float(input(f"Введите элемент {i}: "))
        a.append(complex(value, 0))

    print("Исходный массив:")
    print(a)

    fft(a)

    print("После прямого FFT:")
    print(a)

    fft(a, True)

    print("После обратного FFT:")
    print(a)


main()
