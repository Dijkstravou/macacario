// https://codeforces.com/contest/446/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 3e5 + 10;
const ll inf = LLONG_MAX;
const ll mod = 1000000009 ;

#define pb push_back
#define ppb pop_back 
#define ff first
#define ss second 
#define sza(x) ((int)(x).size())
#define all(a) (a).begin(), (a).end()
#define smax(s, v) s = max(s, (v))
#define smin(s, v) s = min(s, (v))

#define FF(i, n) for(int i = 0; i < (n); i++)
#define FF1(i, n) for(int i = 1; i <= (n); i++)
#define FFZ(i, v) FF(i, sza(v))
#define FFS(i, s, n) for(int i = s; i <= (n); i++)
#define FFD(i, n) for(int i = (n)-1; i >= 0; i--)

#define F(n) FF(i, n)
#define F1(n) FF1(i, n)
#define FZ(v) FFZ(i, v)
#define FS(s, n) FFS(i, s, n)
#define FD(n) FFD(i, n)

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.ff << ", " << p.ss << ")"; }
template<typename A> ostream& operator<<(ostream& os, const vector<A>& v) { os << "["; for(const auto& x: v) os << x << ", "; return os << "]"; }
ostream& printmat(ostream& os, ll v[2][2]) { return os << "[[" << v[0][0] << ", " << v[0][1] << "], [" << v[1][0] << ", " << v[1][1] << "]]"; }

//#define LOCAL
#ifdef LOCAL
void dbg_out() { cerr << endl; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << " " << h; dbg_out(t...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

ll n, m, p, q, k;
ll vec[maxn];
ll fib[maxn],pref[maxn];

ll safemod(ll x) {
    ll r = x % mod;
    return r >= 0 ? r : r+mod;
}

pii calcfib(ll a, ll b, ll i) {
    // i > 0
    // Returns {fib[i], fib[i+1]} where fib[1] = a and fib[2] = b

    dbg(a, b, i);

    pii ret = (i == 1) ? pii{ a, b } : pii{ (fib[i-2] * a + fib[i-1] * b) % mod, (fib[i-1] * a + fib[i] * b) % mod };
    dbg(ret);

    return ret;
}

// 1 indexado

#define LEFT 2*i 
#define RIGHT 2*i+1

#define EL LEFT, l, (l+r)/2 
#define ER RIGHT, (l+r)/2+1, r
#define INI 1, 1, n

struct Node {
    ll v, a=0, b=0;  // Adiciona acumulador 

    Node(ll v=0): v(v) {}
    Node operator+(Node ot) { return Node((v+ot.v) % mod); }

    // Update apenas marca 
    void update(ll ua, ll ub) { a = (a+ua) % mod; b = (b+ub) % mod; }
    // Realmente aplica update. CUIDADO SE NAO VERIFICOU SE TA MARCADO
    void apply(int l, int r) { 
        ll soma = calcfib(a, b, (r-l+1)+4).ff;
        v = safemod(v + soma - a - 2*b);
        a = b = 0;
    }
};

struct Seg {
    Node dt[4*maxn];
    bool mark[4*maxn]; // Se tem update

    Node build(int i, int l, int r) {
        mark[i] = false; // Inicializa mark
        if(l == r) return dt[i] = Node(vec[r]);
        return dt[i] = build(EL) + build(ER);
    }

    void flush(int i, int l, int r) {
        dbg("Flushing ", l, r);

        if(l != r) {
            dt[LEFT].update(dt[i].a, dt[i].b);

            int cnt_left = (l + r) / 2 - l + 1;
            pii f = calcfib(dt[i].a, dt[i].b, cnt_left+1);
            dt[RIGHT].update(f.ff, f.ss);
            mark[LEFT] = mark[RIGHT] = true;
        }
        dt[i].apply(l, r);
        mark[i] = false;
    }

    Node query(int ql, int qr, int i, int l, int r) {
        if(mark[i]) flush(i, l, r);

        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return dt[i];
        return query(ql, qr, EL) + query(ql, qr, ER);
    }

    Node update(int ql, int qr, int v, int i, int l, int r) {
        dbg("Update", l, r);
        if(mark[i]) flush(i, l, r);

        if(l > qr || r < ql) return dt[i];
        if(ql <= l && r <= qr) {
            pii f = calcfib(1, 0, l-ql+1);
            dt[i].update(f.ff, f.ss);
            flush(i, l, r);
            return dt[i];
        }

        return dt[i] = update(ql, qr, v, EL) + update(ql, qr, v, ER);
    }
};

Seg seg;

void solve() {
    cin >> n >> q;
    F1(n) {
    	cin >> vec[i];
    }

    seg.build(INI);

    F(q) {
        int op, l, r;
        cin >> op >> l >> r;

        if(op == 1) {
            seg.update(l, r, l, INI);
        } else {
            cout << seg.query(l, r, INI).v << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    fib[1] = fib[2] = 1;
    FS(3, maxn) fib[i] = (fib[i-1] + fib[i-2]) % mod;
    //F1(maxn-1) pref[i] = (pref[i-1] + fib[i]) % mod;

    solve();
}
