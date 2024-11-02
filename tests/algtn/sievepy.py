L = 10 ** 7
c = [0 for _ in range(L+1)]

c[1] = 1


def crivar(cara):
    m = 2
    while m * cara <= L:
        c[m * cara] = 1
        m += 1


def conta_zeros():
    return c.count(0) - 1


crivar(2)
crivar(3)
crivar(5)

print(conta_zeros())

i = 2
sc = 0
while i <= L:
    sc += 1 - c[i]
    i += 3

print(sc)
