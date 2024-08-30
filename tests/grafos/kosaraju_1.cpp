// https://cses.fi/problemset/task/1686
#include <bits/stdc++.h>
//#define LOCAL

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
vi g[maxn], gt[maxn];
ll a[maxn], b[maxn];

bool vis[maxn];
int nc;
vi dag[maxn];
int root[maxn];

void dfs(int v, vi* g, vi &out) {
	vis[v] = true;
	for(auto u: g[v]) if(!vis[u]) dfs(u, g, out);
	out.pb(v);
}

void gen_dag() {
	vi ord;
	memset(vis, false, sizeof(vis));
	F1(n) if(!vis[i]) dfs(i, g, ord);
	memset(vis, false, sizeof(vis));
	reverse(all(ord));
	for(auto v: ord) if(!vis[v]) {
		vi comp;
		dfs(v, gt, comp);
		int rt = ++nc;
		for(auto u: comp) { root[u] = rt; b[rt] += a[u]; }
	}
	FF1(v, n) for(auto u: g[v])
		if(root[v] != root[u]) dag[root[v]].pb(root[u]);
}

ll dp[maxn];

ll dfs2(int v, int p=-1) {
	if(dp[v]) return dp[v];
	
	ll r = 0;
	for(auto u: dag[v]) if(u != p) smax(r, dfs2(u, v));

	return dp[v] = r+b[v];
}

void solve() {
    cin >> n >> m;
	F1(n) cin >> a[i];
	F(m) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		gt[y].pb(x);
	}
	gen_dag();

	dbg(nc);
	F1(nc) dbg(i, dag[i]);
	
	ll res = 0;
	F1(nc) smax(res, dfs2(i));
	cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 solve();
}
