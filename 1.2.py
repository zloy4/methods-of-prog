import sys
@profile
def main(x, y):
    if x<10 or y<10:
        return x*y
    md = max(len(str(x)), len(str(y))) // 2
    levx, pravx = divmod(x, 10**md)
    levy, pravy = divmod(y, 10**md)
    qw = main(pravx, pravy)
    er = main(levx, levy)
    er_qw = main((levx + pravx), (levy + pravy))
    return qw + (er_qw - er - qw) * 10**md + er*10**(md*2)
result = main(int(sys.argv[1]), int(sys.argv[2]))
print("Multiplication result:", result)
