// acha inversos de a[1], a[2], ..., a[n] mod p primo
// acha em O(n + log p) tempo. Requer O(n) memo

#include "bits/stdc++.h"
using namespace std;

const long long P = 1000000007;
long long qpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return ans;
}

long long n, a[1000010], pre[1000010], suf[1000010], pr = 1; // prefix, suffix, product
int main() {
    cin >> n;
    pre[0] = suf[n + 1] = 1;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] * a[i] % P;
        suf[n + 1 - i] = suf[n + 2 - i] * a[n + 1 - i] % P;
        pr = pr * a[i] % P;
    }
    pr = qpow(pr, P - 2);
    for (int i = 1; i <= n; i++) {
        cout << (pre[i - 1] * suf[i + 1] % P) * pr % P << endl;
    }
}