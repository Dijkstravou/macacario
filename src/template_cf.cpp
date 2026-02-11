#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 2e5 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const unsigned int mod = 1e9 + 7;

#define pb push_back
#define ppb pop_back 
#define ff first
#define ss second 
#define sza(x) ((int)(x).size())
#define all(a) (a).begin(), (a).end()
#define smax(s, v) s = max(s, (v))
#define smin(s, v) s = min(s, (v))

#define FF(i,n) for(int i = 0; i < (n); i++)
#define FF1(i,n) for(int i = 1; i <= (n); i++)
#define FFD(i,n) for(int i = (n)-1; i >= 0; i--)
#define FFD1(i,n) for(int i = (n); i > 0; i--)

#define F(n) FF(i,n)
#define F1(n) FF1(i,n)
#define FD(n) FFD(i,n)
#define FD1(n) FFD1(i,n)

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.ff << ", " << p.ss << ")"; }
template<typename A> ostream& operator<<(ostream& os, const vector<A>& v) { os << "["; for(const auto& x: v) os << x << ", "; return os << "]"; }
template<typename A> ostream& operator<<(ostream& os, const set<A>& v) { os << "{"; for(const auto& x: v) os << x << ", "; return os << "}"; }
template<typename A, typename B> ostream& operator<<(ostream& os, const map<A, B>& v) { os << "{"; for(const auto& par: v) os << par << ", "; return os << "}"; }

#ifdef LOCAL
void dbg_out() { cerr << endl; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << " " << h; dbg_out(t...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int add(int a, int b) {
    a += b;
    // ordem importa para evitar comparacao sinal sem sinal
    if(a<0) return a+mod;  
    if(a >= mod) return a-mod;
    return a;
}
#define sadd(a, b) a = add(a, (b))

int sub(int a, int b) {
    return add(a, -b);
}
#define ssub(a, b) a = sub(a, (b))

int mul(int x, int y) {
    return (ll) x * y % mod;
}
#define smul(a, b) a = mul(a, (b))

int fpow(int x, ll e) {
    int r = 1;
    while(e) {
        if(e&1) smul(r, x);
        smul(x,x);
        e>>=1;
    }
    return r;
}

int modinv(int x) {
    return fpow(x, mod-2);
}

int safemod(ll x) {
    x %= mod;
    return x<0 ? x+mod : x;
}

// ================================================= 
// ================== CODIGO AQUI ==================
// ================================================= 

ll n, m, p, q, k;
ll a[maxn];

void solve() {
    cin >> n;
    F(n) {
    	cin >> a[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    F1(t) solve();
}
