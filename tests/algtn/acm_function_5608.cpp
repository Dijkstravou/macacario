#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const ll mod = 1e9 + 7;

ll fast_expo(ll base, ll expo) {
    ll ans = 1;
    while (expo) {
        if (expo & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        expo >>= 1;
    }
    return ans;
}

ll invmod(ll cara) { return fast_expo(cara, mod - 2); }

const ll inv2 = invmod(2);
const ll inv6 = invmod(6);

// g = 1
ll sg(ll n) { return n % mod; }

// f*g = n^2-3n+2 = (n-1)(n-2)
ll sfg(ll n) {
    ll primeira_parcela = n * (n + 1) % mod;
    primeira_parcela = primeira_parcela * (2 * n + 1) % mod;
    primeira_parcela = (primeira_parcela * inv6) % mod;
    ll segunda_parcela = n * (n + 1) % mod;
    segunda_parcela = (segunda_parcela * inv2) % mod;
    segunda_parcela = (mod - 3) * segunda_parcela % mod;
    segunda_parcela = (segunda_parcela + (2 * n)) % mod;
    return (primeira_parcela + segunda_parcela) % mod;
}

unordered_map<ll, ll> sf;

ll calc(ll n) {
    auto quero = sf.find(n);
    if (quero != sf.end()) return quero->second;
    if (n == 1) return sf[1] = 0;
    ll ans = 0;
    for (ll d = 2, la; d <= n; d = la + 1) {
        la = n / (n / d);
        ll incre = (sg(la) - sg(d - 1) + mod) * calc(n / d) % mod;
        ans = ans + incre;
        if (ans >= mod) ans -= mod;
    }
    ans = sfg(n) - ans + mod;
    if (ans >= mod) ans -= mod;
    // ans = (ans * inverso de g(1)) % mod
    return sf[n] = ans;
}

void solve() {
    ll n;
    cin >> n;
    cout << calc(n) << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}