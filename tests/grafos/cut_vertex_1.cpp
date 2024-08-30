// https://codeforces.com/problemset/problem/193/A
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 64 * 64;
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
vi g[maxn];

int tin[maxn], low[maxn];
int timer;
int res = -1;

void dfs(int v, int p=-1) {
    tin[v] = low[v] = ++timer;
    bool pskip = false;
	int children = 0;
    for(int u: g[v]) {
        if(u == p && !pskip) {
            pskip = true;
            continue;
        }
        if(tin[u] != 0) smin(low[v], tin[u]);
        else {
            dfs(u, v);
            smin(low[v], low[u]);
            if(low[u] >= tin[v] && p != -1) res = v;
			children++;
        }
    }
	
	if(p == -1 && children > 1) res = v;
}

char a[maxn][maxn];

void ade(int i1, int j1, int i2, int j2) {
	int x = (i1-1) * m + j1;
	int y = (i2-1) * m + j2;
	g[x].pb(y);
	g[y].pb(x);
}

void solve() {
    cin >> n >> m;
	F1(n) FF1(j, m) cin >> a[i][j];

	int cnt=0;
	
	F1(n) FF1(j, m) if(a[i][j] == '#') {
		if(a[i+1][j] == '#') ade(i, j, i+1, j);
		if(a[i][j+1] == '#') ade(i, j, i, j+1);
		cnt++;
	}
	
	if(cnt < 3) {
		cout << -1 << endl;
		return;
	}

	F1(n*m) if(tin[i] == 0) dfs(i);

	if(res != -1) cout << 1 << endl;
	else cout << 2 << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

	solve();
}
