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


def multiply_fft(number1, number2):
    a = []

    for digit in reversed(number1):
        a.append(complex(int(digit), 0))

    b = []

    for digit in reversed(number2):
        b.append(complex(int(digit), 0))

    n = 1

    while n < len(a) + len(b):
        n *= 2

    a += [0] * (n - len(a))
    b += [0] * (n - len(b))

    fft(a)
    fft(b)

    for i in range(n):
        a[i] *= b[i]

    fft(a, True)

    result = []

    for value in a:
        result.append(round(value.real))

    carry = 0

    for i in range(len(result)):
        current = result[i] + carry

        result[i] = current % 10
        carry = current // 10

    while carry > 0:
        result.append(carry % 10)
        carry //= 10

    while len(result) > 1 and result[-1] == 0:
        result.pop()

    answer = ""

    for digit in reversed(result):
        answer += str(digit)

    return answer


a = input("Введите первое число: ")
b = input("Введите второе число: ")

result = multiply_fft(a, b)

print("Результат:", result)
