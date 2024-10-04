#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const ll mod = 30011;

int potencias[25];

int size_lim = 1 << 16;

ll fast_expo(ll base, ll expo) {
    ll ans = 1;
    while (expo > 0) {
        if (expo & 1) ans = (base * ans) % mod;
        base = (base * base) % mod;
        expo >>= 1;
    }
    return ans;
}

ll inverse(ll cara) { return fast_expo(cara, mod - 2); }

const ll rev = inverse(2);

void FWT(vector<ll>& a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) % mod, a[i + j + d] = (x - y + mod) % mod;
                // xor:a[i+j]=x+y,a[i+j+d]=x-y;
                // and:a[i+j]=x+y;
                // or:a[i+j+d]=x+y;
            }
}

void UFWT(vector<ll>& a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = 1LL * (x + y) * rev % mod,
                      a[i + j + d] = (1LL * (x - y) * rev % mod + mod) % mod;
                // xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                // and:a[i+j]=x-y;
                // or:a[i+j+d]=y-x;
            }
}

vector<ll> mul(const vector<ll>& v1, const vector<ll>& v2) {
    vector<ll> p1(v1.begin(), v1.end());
    vector<ll> p2(v2.begin(), v2.end());
    vector<ll> res;
    int novosize = 1;
    // printa(p1);
    // printa(p2);
    while (p1.size() + p2.size() > novosize) {
        novosize <<= 1;
    }
    p1.resize(novosize);
    p2.resize(novosize);
    res.resize(novosize);
    FWT(p1, novosize);
    FWT(p2, novosize);
    for (int i = 0; i < novosize; i++)
        res[i] = (p1[i] * p2[i]) % mod;
    UFWT(res, novosize);
    if (novosize > size_lim) res.resize(size_lim);
    return res;
}

vector<ll> fast_expo(const vector<ll>& base, ll expo) {
    vector<ll> the_ans(base.size(), 0);
    the_ans[0] = 1;
    vector<ll> cp_base(base.begin(), base.end());
    while (expo > 0) {
        if (expo & 1) the_ans = mul(the_ans, cp_base);
        cp_base = mul(cp_base, cp_base);
        expo >>= 1;
    }
    return the_ans;
}

int main() {
    int i2 = inverse(2);
    // cout << "aa " << i2 << "\n";
    potencias[0] = 1;
    for (int i = 1; i < 25; i++) {
        potencias[i] = (i2 * potencias[i - 1]) % mod;
    }
    int n, k;
    cin >> n >> k;
    vector<ll> the_pol(k + 1, 1);
    vector<ll> exponenciado = fast_expo(the_pol, n);
    ll ans = 0;
    for (int i = 1; i < exponenciado.size(); i++) {
        ans = (ans + exponenciado[i]) % mod;
    }
    printf("%lld\n", ans);
}