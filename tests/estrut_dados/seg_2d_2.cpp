// https://codeforces.com/contest/677/problem/D
// Da certo em muitos casos, mas eh lento
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 310;
const ll maxm = maxn;
const ll inf = 1e12;

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

//#define LOCAL
#ifdef LOCAL
void dbg_out() { cerr << endl; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << " " << h; dbg_out(t...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

ll n, m, p, q, k;
int a[maxn][maxm];

// 1 indexado

#define EL 2*i, l, (l+r)/2 
#define ER 2*i+1, (l+r)/2+1, r
#define INI 1, 1, n
#define INIY 1, 1, m

struct Node {
    pii v;

    Node(pii v={1, inf}): v(v) {}
    Node operator+(Node ot) { return Node(min(v, ot.v)); }
    void update(pii _v) {v = _v;}
};

struct Seg {
    Node dt[4*maxn][4*maxm];

	Node query_y(int ql, int qr, int xi, int i, int l, int r) {
		if(l > qr || r < ql) return Node();
		if(ql <= l && r <= qr) return dt[xi][i];
		return query_y(ql, qr, xi, EL) + query_y(ql, qr, xi, ER);
	}

	Node query_x(int ql, int qr, int qyl, int qyr, int i, int l, int r) {
		if(l > qr || r < ql) return Node();
		if(ql <= l && r <= qr) return query_y(qyl, qyr, i, INIY);
		return query_x(ql, qr, qyl, qyr, EL) + query_x(ql, qr, qyl, qyr, ER);
	}

	Node update_y(int qy, pii novo, int xi, int xl, int xr, int i, int l, int r) {
		if(r < qy || l > qy) return dt[xi][i];
		if(l == r) {
			if(xl == xr) dt[xi][i].update(novo);
			else dt[xi][i] = dt[xi*2][i] + dt[xi*2+1][i];
			return dt[xi][i];
		}
		return dt[xi][i] = update_y(qy, novo, xi, xl, xr, EL) + update_y(qy, novo, xi, xl, xr, ER);
	}

	void update_x(int qx, int qy, pii novo, int i, int l, int r) {
		if(r < qx || l > qx) return;
		if(l != r) {
			update_x(qx, qy, novo, EL); update_x(qx, qy, novo, ER);
		}
		update_y(qy, novo, i, l, r, INIY);
	}

	ll query(int qxl, int qxr, int qyl, int qyr, int t) {
		pii res = query_x(qxl, qxr, qyl, qyr, INI).v;
		if(res.ff != -(t-1)) return inf;
		return res.ss;
	}
};

Seg s0, s1, s2, s3;   // Clockwise

vector<pii> pos_by_type[maxn*maxm];
ll dp[maxn][maxm];

void solve() {
    cin >> n >> m >> p;
	
    F1(n) FF1(j , m) {
    	cin >> a[i][j];
		pos_by_type[a[i][j]].pb({i, j});
    }

	pos_by_type[0].pb({1, 1});
	
	FF(t, p+1) {
		if(t>0) {		
			for(auto [i, j]: pos_by_type[t]) {
				ll res = i+j + s0.query(1, i, 1, j, t);
				smin(res, i-j + s1.query(1, i, j, m, t));
				smin(res, -i-j + s2.query(i, n, j, m, t));
				smin(res, -i+j + s3.query(i, n, 1, j, t));

				if(t == p) {
					cout << res << '\n';
					return;
				}

				dp[i][j] = res;
				dbg(t, i, j, res);
			}
			
			/*for(auto [i, j]: pos_by_type[t-1]) {
				s0.update_x(i, j, inf, INI);
				s1.update_x(i, j, inf, INI);
				s2.update_x(i, j, inf, INI);
				s3.update_x(i, j, inf, INI);
				}*/
		}

		for(auto [i, j]: pos_by_type[t]) {
			s0.update_x(i, j, {-t, dp[i][j] - i - j}, INI);
			s1.update_x(i, j, {-t, dp[i][j] - i + j}, INI);
			s2.update_x(i, j, {-t, dp[i][j] + i + j}, INI);
			s3.update_x(i, j, {-t, dp[i][j] + i - j}, INI);
		}
	}
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 solve();
}
