//https://cses.fi/problemset/task/1686/
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
ll a[maxn], b[maxn];

int tin[maxn], low[maxn];
int timer;
int nc;
int root[maxn];
vi g[maxn];

void dfs(int v, vi &st) {
    tin[v] = low[v] = ++timer;
	st.pb(v);
	
    for(int u: g[v]) {
        if(tin[u] == 0) dfs(u, st);
		if(root[u] == 0) smin(low[v], low[u]);
    }

	if(low[v] == tin[v]) {
		int lst;
		++nc;		
		do {
			lst = st.back();
			st.ppb();
			root[lst] = nc;
		} while(lst != v);
	}
}

vi dag[maxn];
ll dp[maxn];

ll dfs2(int v,int p=-1) {
	if(dp[v]) return dp[v];

	ll r = 0;
	for(auto u: dag[v]) if(u != p) smax(r, dfs2(u, v));
	return dp[v] = r+b[v];
}

void solve() {
    cin >> n >> m;
    F1(n) {
    	cin >> a[i];
    }
	F(m) {
		int u, v;
		cin >>u >> v;
		g[u].pb(v);
	}
	
	F1(n) if(tin[i] == 0) {
		vi st;
		dfs(i, st);
	}

	F1(n) for(auto j: g[i]) if(root[i] != root[j]) dag[root[i]].pb(root[j]);
	F1(n) b[root[i]] += a[i];

	ll r = 0;
	F1(nc) smax(r, dfs2(i));
	cout << r << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 solve();
}
