BASE = 10000


def to_digits(number):
    digits = []

    while len(number) > 0:
        start = max(0, len(number) - 4)
        block = number[start:]

        digits.append(int(block))
        number = number[:start]

    return digits


def from_digits(digits):
    while len(digits) > 1 and digits[-1] == 0:
        digits.pop()

    result = str(digits[-1])

    for i in range(len(digits) - 2, -1, -1):
        result += str(digits[i]).zfill(4)

    return result


def multiply(a, b):
    result = [0] * (len(a) + len(b))

    for i in range(len(a)):
        for j in range(len(b)):
            result[i + j] += a[i] * b[j]

    for i in range(len(result) - 1):
        carry = result[i] // BASE
        result[i] %= BASE
        result[i + 1] += carry

    return result


a = input("Введите первое число: ")
b = input("Введите второе число: ")

a_digits = to_digits(a)
b_digits = to_digits(b)

result = multiply(a_digits, b_digits)

print("Результат:", from_digits(result))
