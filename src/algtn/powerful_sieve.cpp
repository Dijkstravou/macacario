#define MAX 100000000
#define LMT 10000

int flag[MAX / 64];
int primes[5761460], total;

#define chkC(n) (flag[n >> 6] & (1 << ((n >> 1) & 31)))
#define setC(n) (flag[n >> 6] |= (1 << ((n >> 1) & 31)))

void sieve() {
    int i, j, k;
    flag[0] |= 0;
    for (i = 3; i < LMT; i += 2)
        if (!chkC(i))
            for (j = i * i, k = i << 1; j < MAX; j += k)
                setC(j);
    primes[(j = 0)++] = 2;
    for (i = 3; i < MAX; i += 2)
        if (!chkC(i)) primes[j++] = i;
    total = j;
}