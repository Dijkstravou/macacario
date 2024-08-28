// https://codeforces.com/problemset/problem/869/E
// Nao terminei, tem que ter lazy, pqp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 2e3 + 10;
const ll maxm = maxn;
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

// 1 indexado

#define EL 2*i, l, (l+r)/2 
#define ER 2*i+1, (l+r)/2+1, r
#define INI 1, 1, n
#define INIY 1, 1, m

struct Node {
    ll v;

    Node(ll v=0): v(v) {}
    Node operator+(Node ot) { return Node(v+ot.v); }
    void update(ll _v) {v = _v;}
};

struct Seg {
    Node dt[4*maxn][4*maxm];

	void buildy(int xi, int xl, int xr, int i, int l, int r) {
		if(l == r) {
			if(xl == xr) dt[xi][i] = 0;
			else dt[xi][i] = dt[xi*2][i] + dt[xi*2+1][i];
		} else {
			buildy(xi, xl, xr, EL); buildy(xi, xl, xr, ER);
			dt[xi][i] = dt[xi][i*2] + dt[xi][i*2+1];
		}
	}
	
	void buildx(int i, int l, int r) {
		if(l != r) { buildx(EL); buildx(ER); }
		buildy(i, l, r, INIY);
	}

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

	Node update_y(int qy, int novo, int xi, int i, int l, int r) {
		if(r < qy || l > qy) return dt[xi][i];
		if(l == r) {
			dt[xi][i].update(novo);
			return dt[xi][i];
		}
		return dt[xi][i] = update_y(qy, novo, xi, EL) + update_y(qy, novo, xi, ER);
	}

	void update_x(int qx, int qy, int novo, int i, int l, int r) {
		if(r < qx || r > qx) return;
		if(l != r) {
			update_x(qx, qy, novo, EL); update_x(qx, qy, novo, ER);
		}
		update_y(qy, novo, i, INIY);
	}
};

Seg seg;

void solve() {
	cin >> n >> m >> q;

	seg.buildx(INI);

	int cur = 0;
	
	F(q) {
		int t, x1, y1, x2, y2;
		cin >> t >> x1 >> y1 >> x2 >> y2;
		if(t == 1) {
			//seg.update_x();
		} else if(t == 2) {
			
		} else {
			
		}
	}
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

solve();
}
