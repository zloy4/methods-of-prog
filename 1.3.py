import sys
import math
import cmath
@profile
def main(x, y):
    def bpf(x):
        dlina = len(x)
        if dlina <= 1:
            return x
        even = bpf(x[0::2])
        uneven = bpf(x[1::2])
        rez = [0] * dlina
        for i in range(dlina // 2):
            rez[i] = even[i] + cmath.exp(-2j * cmath.pi * i / dlina) * uneven[i]
            rez[i + dlina // 2] = even[i] - cmath.exp(-2j * cmath.pi * i / dlina) * uneven[i]
        return rez
    def obpf(x):
        dlina = len(x)
        if dlina <= 1:
            return x
        even = obpf(x[0::2])
        uneven = obpf(x[1::2])
        rez = [0] * dlina
        for i in range(dlina // 2):
            rez[i] = even[i] + cmath.exp(2j * cmath.pi * i / dlina) * uneven[i]
            rez[i + dlina // 2] = even[i] - cmath.exp(2j * cmath.pi * i / dlina) * uneven[i]
        return rez
    x = str(x)
    y = str(y)
    xlen = len(x)
    ylen = len(y)
    dlina = 1
    while dlina < xlen + ylen:
        dlina *= 2
    p = [0] * dlina
    q = [0] * dlina
    for k in range(xlen):
        p[k] = int(x[xlen - 1 - k])
    for k in range(ylen):
        q[k] = int(y[ylen - 1 - k])
    a = bpf(p)
    b = bpf(q)
    c = [0] * dlina
    for k in range(dlina):
        c[k] = a[k]*b[k]
    cq = obpf(c)
    result = 0
    for k in range(len(cq)):
        chisl = round(cq[k].real / dlina)
        result += chisl * (10 ** k)
    return result
result = main(int(sys.argv[1]), int(sys.argv[2]))
print("Multiplication result:", result)
