// https://oj.uz/problem/view/IZhO12_apple
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

//#define LOCAL
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
// Note que EL, ER mudaram um pouco

#define EL l, (l + r) / 2
#define ER (l + r) / 2 + 1, r
#define INI &seg.root, 1, n

struct Node {
    ll v;
	bool full;
    Node *l, *r;

    Node(ll v = 0) : v(v), l(0), r(0), full(0) {}
	void merge(Node l, Node r) {
		v = l.v + r.v;
		full = l.full && r.full;
	}
	void merge() { merge(*l, *r); }
	void update(ll l, ll r) {
		v = r - l + 1;
		full = 1;
	}
};

struct Seg {
	Node root;

	// Cuidado se for fazer lazy, tem que verificar se nao eh folha antes
	inline void extend(Node *v) {
		if(v->l == 0) {
			v->l = new Node();
			v->r = new Node();
		}
	}

	void update(ll ql, ll qr, Node *v, ll l, ll r) {
		dbg("Upd in", v->v, v->full, l, r);
		if(v->full || l > qr || r < ql) { dbg("Nao mudou", l, r); return;}
		if(ql <= l && r <= qr) {			
			v->update(l, r);
			dbg("Cheio", l, r, v->v, v->full);
			return;
		}
		
		extend(v);
		update(ql, qr, v->l, EL); update(ql, qr, v->r, ER);
		v->merge();
		dbg("Merge", l, r, v->v, v->full);
	}

    Node query(int ql, int qr, Node *v, int l, int r) {
		dbg("Query in", v->v, v->full, l, r);
		
        if(l > qr || r < ql) { dbg("Zero", l, r); return Node(); }
        if(ql <= l && r <= qr) { dbg("Proprio", l, r, v->v, v->full); return *v; }
		if(v->full) {
			Node res = Node( min(r, qr) - max(l, ql) + 1 );
			dbg("Inter", l, r, res.v, res.full);
			return res;
		}

		extend(v);
		
		Node res;
		res.merge(query(ql, qr, v->l, EL), query(ql, qr, v->r, ER));
		dbg("Merge", l, r, res.v, res.full);
        return res;
    }
};

Seg seg;

void solve() {
    cin >> m;
	n = 1 << 30;

	ll c = 0;
	
    F(m) {
		ll d, a, b;
		cin >> d >> a >> b;

		a += c;
		b += c;
		
		if(d == 1) {
			ll tmp = seg.query(a, b, INI).v;
			c = tmp;
			cout << tmp << '\n';
		} else {
			seg.update(a, b, INI);
		}
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

solve();
}

