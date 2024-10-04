#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const ll mod = 1e9 + 7;

ll fast_mod(ll k) {
    while (k >= mod)
        k -= mod;
    return k;
}

void FWT(vector<ll>& a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = fast_mod(x + y);
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
                a[i + j] = fast_mod(x - y + mod);
                // xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                // and:a[i+j]=x-y;
                // or:a[i+j+d]=y-x;
            }
}

ll fe(ll base, int expo) {
    ll ans = 1;
    while (expo) {
        if (expo & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        expo >>= 1;
    }
    return ans;
}

int main() {
    int n, ai;
    cin >> n;
    vector<ll> pol_ini(1e6 + 1, 0);
    pol_ini[0] = 1;
    for (int i = 0; i < n; i++) {
        cin >> ai;
        pol_ini[ai] = 1;
    }
    while (!pol_ini.back())
        pol_ini.pop_back();

    int novosize = 1;
    while (novosize < pol_ini.size())
        novosize <<= 1;

    pol_ini.resize(novosize);
    FWT(pol_ini, novosize);
    for (int i = 0; i < novosize; i++) {
        pol_ini[i] = fe(pol_ini[i], n);
    }
    UFWT(pol_ini, novosize);

    int resp = 0;
    for (auto val : pol_ini) {
        if (val) resp++;
    }
    cout << resp << "\n";
}