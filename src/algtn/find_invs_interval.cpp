// acha inversos de 1 a n mod p primo
// acha em O(n) tempo. Requer O(n) memo

int n = 10, p = 1000000007;
int inv[n + 1];
inv[1] = 1;
for (int i = 2; i <= n; i++)
    inv[i] = 1LL * (p - p / i) * inv[p % i] % p;
