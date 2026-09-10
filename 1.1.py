import sys
@profile
def main(x, y):
    ans = 0
    q = 0
    l = 0
    a = str(x)[::-1]
    b = str(y)[::-1]
    for i in range(len(b)):
        c = ''
        h = 0
        for j in range(len(a)):
            q = int(a[j]) * int(b[i]) + h
            h = q//10
            l = q%10
            c += str(l)
        if h>0:
            c += str(h)
        ans += int(c[::-1]) * (10**i)
    return ans
result = main(int(sys.argv[1]), int(sys.argv[2]))
print("Multiplication result:", result)
