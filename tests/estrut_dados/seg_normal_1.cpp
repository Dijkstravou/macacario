// https://codeforces.com/problemset/problem/339/D
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 2e5 + 10;
const ll inf = LLONG_MAX;

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

#ifdef LOCAL
void dbg_out() { cerr << endl; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << " " << h; dbg_out(t...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

ll n, m, p, q, k;
ll a[maxn];

// 1 indexado

#define EL 2*i, l, (l+r)/2 
#define ER 2*i+1, (l+r)/2+1, r
#define INI 1, 1, n

struct Node {
    ll v, md;

    Node(ll v=0, ll md=0): v(v), md(md) {}
    Node operator+(Node ot) { return Node(md ? (v^ot.v) : (v|ot.v), 1^md); }
    void update(ll _v) {v = _v;}
};

struct Seg {
    Node dt[4*maxn];

    Node build(int i, int l, int r) {
        if(l == r) return dt[i] = Node(a[r]);
        return dt[i] = build(EL) + build(ER);
    }

    Node query(int ql, int qr, int i, int l, int r) {
        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return dt[i];
        return query(ql, qr, EL) + query(ql, qr, ER);
    }

    Node update(int pos, int v, int i, int l, int r) {
        if(r < pos || l > pos) return dt[i];
        if(l == r) {
            dt[i].update(v);
            return dt[i];
        }

        return dt[i] = update(pos, v, EL) + update(pos, v, ER);
    }
};

Seg seg;

void solve() {
    cin >> n >> q;
    n = (1 << n);
    F1(n) {
    	cin >> a[i];
    }

    seg.build(INI);

    F(q) {
        ll p, b;
        cin >> p >> b;

        seg.update(p, b, INI);
        cout << seg.dt[1].v << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
