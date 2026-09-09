def karatsuba(x, y):
    if x == "0" or y == "0":
        return "0"

    if len(x) == 1 or len(y) == 1:
        return str(int(x) * int(y))

    n = max(len(x), len(y))

    if n % 2 != 0:
        n += 1

    x = x.zfill(n)
    y = y.zfill(n)

    m = n // 2

    a1 = x[:m]
    a0 = x[m:]

    b1 = y[:m]
    b0 = y[m:]

    p1 = karatsuba(a1, b1)
    p2 = karatsuba(a0, b0)
    p3 = karatsuba(str(int(a1) + int(a0)),
                   str(int(b1) + int(b0)))

    middle = int(p3) - int(p1) - int(p2)

    result = (
        int(p1) * 10 ** (2 * m)
        + middle * 10 ** m
        + int(p2)
    )

    return str(result)


a = input("Введите первое число: ")
b = input("Введите второе число: ")

result = karatsuba(a, b)

print("Результат:", result)
