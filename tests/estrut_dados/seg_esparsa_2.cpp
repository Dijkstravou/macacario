// https://oj.uz/problem/view/Balkan15_HAPPINESS
// Essa versao estoura a memoria nos ultimos casos, mas funciona no resto.
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

#ifndef LOCAL
#include "happiness.h"
#endif

ll n, m, p, q, k;

// 1 indexado
// Note que EL, ER mudaram um pouco

#define EL l, (l + r) / 2
#define ER (l + r) / 2 + 1, r
#define INI &seg.root, 1, n

struct Node {
	// cnt eh util so para folha
    ll cnt, sum, rem;
    Node *l, *r;

    Node() : l(0), r(0), sum(0), rem(0), cnt(0) {}
	void merge(Node l, Node r) {
		sum = l.sum + r.sum;
		rem = max(l.rem, r.rem - l.sum);
	}
	void merge() { merge(*l, *r); }
	void update(ll v, int d) {
		cnt += d;
		sum = v * cnt;

		if(cnt == 0) rem = 0;
		else rem = v-1;
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

	void update(ll pos, ll x, Node *v, ll l, ll r) {
		if(r < pos || l > pos) return;
		if(l == r) {
			v->update(r, x);
			return;
		}
		
		extend(v);
		update(pos, x, v->l, EL); update(pos, x, v->r, ER);
		v->merge();
	}

    Node query(int ql, int qr, Node *v, int l, int r) {
        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return *v;

		extend(v);
		
		Node res;
		res.merge(query(ql, qr, v->l, EL), query(ql, qr, v->r, ER));
        return res;
    }
};

Seg seg;

bool init(int coinsCount, long long maxCoinSize, long long coins[]) {
	n = maxCoinSize;
	
	F(coinsCount) seg.update(coins[i], 1, INI);
	return seg.root.rem == 0;
}

bool is_happy(int event, int coinsCount, long long coins[]) {
	F(coinsCount) seg.update(coins[i], event, INI);
	return seg.root.rem == 0;
}


#ifdef LOCAL
ll _coins[maxn];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

	ll n, m, q;
	cin >> n >> m;
	F(n) cin >> _coins[i];

	cout << init(n, m, _coins) << '\n';
	
	cin >> q;
	FF(__i, q) {
		ll d, k;
		cin >> d >> k;
		F(k) cin >> _coins[i];
		cout << is_happy(d, k, _coins) << "\n";
	}
}
#endif

