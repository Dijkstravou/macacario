//https://codeforces.com/contest/1986/problem/F
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
vector<int> g[maxn];

int tin[maxn], low[maxn], sz[maxn];
int timer;
vector<pii> res;

void dfs(int v, int p=-1) {
    tin[v] = low[v] = ++timer;
    bool pskip = false;
    sz[v] = 1;

    for(int u: g[v]) {
        if(u == p && !pskip) {
            pskip = true;
            continue;
        }
        if(tin[u] != 0) smin(low[v], tin[u]);
        else {
            dfs(u, v);
            smin(low[v], low[u]);
            if(low[u] > tin[v]) res.pb({v, u});
            sz[v] += sz[u];
        }
    }
}

void find_bridges() {
    F1(n) if(tin[i] == 0) dfs(i);
}

void solve() {
    cin >> n >> m;
    F1(n) g[i].clear();
    timer = 0;
    res.clear();
    memset(tin, 0, sizeof(tin));
    memset(sz, 0, sizeof(sz));

    F(m) {
        int u, v;
        cin >> u >> v;
    	g[u].pb(v);
        g[v].pb(u);
    }

    find_bridges();

    ll c = n * (n-1)/2;
    for(auto [u, v]: res) {
        ll a = sz[v];
        ll b = n-a;

        smin(c, a*(a-1) / 2 + b*(b-1)/2);
    }

    cout << c << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    F1(t) solve();
}

