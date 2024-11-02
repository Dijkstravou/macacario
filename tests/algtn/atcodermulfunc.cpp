#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pcc pair<char, char>
#define vi vector<int>
#define vl vector<ll>
#define sd(x) scanf("%d", &x)
#define slld(x) scanf("%lld", &x)
#define pd(x) printf("%d", x)
#define plld(x) printf("%lld", x)
#define pds(x) printf("%d ", x)
#define pllds(x) printf("%lld ", x)
#define pdn(x) printf("%d\n", x)
#define plldn(x) printf("%lld\n", x)
using namespace std;
ll powmod(ll base, ll exponent, ll mod) {
    ll ans = 1;
    if (base < 0) base += mod;
    while (exponent) {
        if (exponent & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        exponent /= 2;
    }
    return ans;
}
ll gcd(ll a, ll b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
const int INF = 2e9;
const ll INFLL = 4e18;
const int small_lim = 4e6 + 1; // maxn^(2/3)
const int mod = 998244353;
const int big_lim = 2.5e3 + 1; // maxn^(1/3)
ll primes_till_i[small_lim];
ll notm2primes_till_i[small_lim];
ll primes_till_bigger_i[big_lim];
ll notm2primes_till_bigger_i[big_lim];
vl sieved_primes[small_lim];
vl sieved_primes_big[big_lim];
vl sieved_primes_m3[small_lim];
vl sieved_primes_big_m3[big_lim];
vl prime;
ll N, m;
void sieve() {
    vi lpf(small_lim);
    ll pw;
    for (int i = 2; i < small_lim; i++) {
        if (!lpf[i]) {
            prime.pb(i);
            lpf[i] = i;
        }
        for (int j : prime) {
            if ((j > lpf[i]) || (j * i >= small_lim)) break;
            lpf[j * i] = j;
        }
    }
    for (int i = 2; i < small_lim; i++) {
        primes_till_i[i] = primes_till_i[i - 1] + (lpf[i] == i);
        notm2primes_till_i[i] = notm2primes_till_i[i - 1] + ((lpf[i] == i) && (i % 3 == 2));
    }
}
ll count_primes(ll n, int ind) {
    if (ind < 0) return n - 1;
    if (1ll * prime[ind] * prime[ind] > n) {
        if (n < small_lim) return primes_till_i[n];
        if (primes_till_bigger_i[N / n]) return primes_till_bigger_i[N / n];
        int l = -1, r = ind;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (1ll * prime[mid] * prime[mid] > n)
                r = mid;
            else
                l = mid;
        }
        return primes_till_bigger_i[N / n] = count_primes(n, l);
    }
    int sz;
    if (n < small_lim)
        sz = sieved_primes[n].size();
    else
        sz = sieved_primes_big[N / n].size();
    ll ans;
    if (sz <= ind) {
        ans = count_primes(n, ind - 1);
        ans -= count_primes(n / prime[ind], ind - 1);
        ans += ind;
        ans += mod;
        ans %= mod;
        if (n < small_lim)
            sieved_primes[n].pb(ans);
        else
            sieved_primes_big[N / n].pb(ans);
    }
    if (n < small_lim)
        return sieved_primes[n][ind];
    else
        return sieved_primes_big[N / n][ind];
}
ll count_primes(ll n) {
    if (n < small_lim) return primes_till_i[n];
    if (primes_till_bigger_i[N / n]) return primes_till_bigger_i[N / n];
    return count_primes(n, prime.size() - 1);
}

ll count_multiples3(ll n, ll ind) {
    if (ind == 0) return n / 3 - n / 6;
    return n - 1;
}

int limitante = 0;

ll count_primes_m3(ll n, int ind) {
    if (ind < 0) return (n + 1) / 3;

    if (1ll * prime[ind] * prime[ind] > n) {
        if (n < small_lim) return notm2primes_till_i[n];
        if (notm2primes_till_bigger_i[N / n]) return notm2primes_till_bigger_i[N / n];
        int l = -1, r = ind;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (1ll * prime[mid] * prime[mid] > n)
                r = mid;
            else
                l = mid;
        }
        return notm2primes_till_bigger_i[N / n] = count_primes_m3(n, l);
    }
    int sz;
    if (n < small_lim)
        sz = sieved_primes_m3[n].size();
    else
        sz = sieved_primes_big_m3[N / n].size();
    ll ans;
    if (sz <= ind) {
        ans = count_primes_m3(n, ind - 1);
        ll val_ans_antes = ans;
        ll anterior, outro, cm3;
        if (prime[ind] % 3 == 1) {
            anterior = count_primes_m3(n / prime[ind], ind - 1);
            ans -= anterior;
            ans += mod;
        } else if (ind == 1) {
            //
        } else {
            anterior = count_primes_m3(n / prime[ind], ind - 1);
            outro = count_primes(n / prime[ind], ind - 1);
            ans -= outro - anterior;
            ans += mod;
            if (ind == 0) {
                // tira 2 . q, q eh 1 mod 3 de 1 ate floor(n/2)
                cm3 = (n / 2) / 3; // n/6
                ans += cm3;
            }
            // ans--; // 2 . 1
        }
        ans %= mod;
        if (limitante++ <= 10) {
            cout << n << " " << ind << " " << prime[ind] << " " << ans << " --- ";
            cout << "ante = " << anterior << " /// outro=" << outro << " /// ";
            cout << "cm3 = " << cm3 << " val_antes = " << val_ans_antes << "\n";
            cout << cm3 + val_ans_antes + anterior - outro << "\n";
        }
        if (n < small_lim)
            sieved_primes_m3[n].pb(ans);
        else
            sieved_primes_big_m3[N / n].pb(ans);
    }
    if (n < small_lim)
        return sieved_primes_m3[n][ind];
    else
        return sieved_primes_big_m3[N / n][ind];
}

// 2 mod 3
ll count_primes_m3(ll n) {
    if (n < small_lim) return notm2primes_till_i[n];
    if (notm2primes_till_bigger_i[N / n]) return notm2primes_till_bigger_i[N / n];
    return count_primes_m3(n, prime.size() - 1);
}

const int ncrlim = 3.5e6;

ll fact[ncrlim];
ll invfact[ncrlim];

void init_fact() {
    fact[0] = 1;
    for (int i = 1; i < ncrlim; i++)
        fact[i] = (1ll * fact[i - 1] * i) % mod;
    invfact[ncrlim - 1] = powmod(fact[ncrlim - 1], mod - 2, mod);
    for (int i = ncrlim - 1; i > 0; i--)
        invfact[i - 1] = (1ll * invfact[i] * i) % mod;
}

ll ncr(ll n, ll r) {
    if (r > n || r < 0) return 0;
    int ans = fact[n];
    ans = (1ll * ans * invfact[n - r]) % mod;
    ans = (1ll * ans * invfact[r]) % mod;
    return ans;
}

ll calculate_dp(ll n, int ind) {
    if (n == 0) return 0;
    if (prime[ind] > n) return 1;
    ll ans = 1, temp;
    if (1ll * prime[ind] * prime[ind] > n) {
        // temp = ncr(k + d, d); f(p)
        temp = m;
        temp *= count_primes(n) - ind;
        ans += temp;
        ans %= mod;
        return ans;
    }
    ans = 0;
    ll gg = 1;
    int expo = 0;
    int mult = 0;
    while (gg <= n) {
        temp = calculate_dp(n / gg, ind + 1);
        temp *= ncr(mult + m - 1, mult); // f(p^k)
        mult++;
        ans += temp;
        ans %= mod;
        gg *= prime[ind];
    }
    return ans;
}

ll calculate_dp2(ll n, int ind) {
    if (n == 0) return 0;
    if (prime[ind] > n) return 1;
    ll ans = 1, temp;
    if (1ll * prime[ind] * prime[ind] > n) {
        temp = m;
        temp *= (count_primes(n) - count_primes_m3(n)) -
                (count_primes(prime[ind] - 1) - count_primes_m3(prime[ind] - 1));
        // cerr << "Primos ate " << n << " = " << count_primes(n) << "\n";
        // cerr << "Primos ate " << prime[ind] - 1 << " = " << count_primes(prime[ind] - 1) << "\n";
        // cerr << "Primos (2) ate " << n << " = " << count_primes_m3(n) << "\n";
        // cerr << "Primos (2) ate " << prime[ind] - 1 << " = " << count_primes_m3(prime[ind] - 1)
        //     << "\n";
        ans += temp;
        ans %= mod;
        // cerr << "dp2 " << n << " " << ind << " " << ans << "\n";
        return ans;
    }
    ans = 0;
    ll gg = 1;
    int expo = 0;
    int mult = 0;
    ll soma_divs = 1;
    while (gg <= n) {
        if (soma_divs % 3 != 0) {
            temp = calculate_dp2(n / gg, ind + 1);
            temp *= ncr(mult + m - 1, mult); // g(p^k)
            ans += temp;
            ans %= mod;
        }
        mult++;
        gg *= prime[ind];
        soma_divs += gg;
    }
    // cerr << "dp2 " << n << " " << ind << " " << ans << "\n";
    return ans;
}

/*
x_1 + ... + x_m = k
f(p^k) = C(k + m - 1, k)
sigma3d(n) = 0 se 3 | sigma(n), 1 c.c.
g(n) = f(n) sigma3d(n)
resposta eh a soma de f - a soma de g

*/

int main() {
    init_fact();
    sieve();
    cout << prime[0] << ", " << prime[1] << ", " << prime[2] << "\n";
    int t = 1;
    cerr << "huh\n";
    while (t--) {
        cin >> N >> m;
        cerr << "here\n";
        ll soma_todo = calculate_dp(N, 0);
        cerr << "aqui2\n";
        ll soma_sub = calculate_dp2(N, 0);
        cerr << "a soma todo vale " << soma_todo << "\n";
        cerr << "a somasub vale " << soma_sub << "\n";
        cout << (soma_todo - soma_sub + mod) % mod << "\n";
        /*for (int i = 1; i < big_lim; i++) {
            primes_till_bigger_i[i] = 0;
            sieved_primes_big[i].clear();
        }*/
    }
    return 0;
}