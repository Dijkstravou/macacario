
//https://codeforces.com/blog/entry/76531
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 2e5 + 10;
const int maxop = 100000 + 10;
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
// Note que EL, ER mudaram um pouco

#define EL l, (l+r)/2 
#define ER (l+r)/2+1, r
#define INI 1, n

struct Node {
    ll v;
    Node *l, *r;

    Node(ll v=0): v(v), l(0), r(0) {}
    Node(Node *l, Node *r): l(l), r(r), v(0) {
        // Merge de nos eh aqui
        if(l) v += l->v;
        if(r) v += r->v;
    }
};

Node* roots[maxop];

Node* build(int l, int r) {
    if(l == r) return new Node(a[r]);
    return new Node(build(EL), build(ER));
}

// Atenção que aqui não retorna ponteiro
Node query(int ql, int qr, Node *v, int l, int r) {
    if(l > qr || r < ql) return Node();
    if(ql <= l && r <= qr) return *v;
    Node q1 = query(ql, qr, v->l, EL), q2 = query(ql, qr, v->r, ER);
    return Node(&q1, &q2);
}

Node* update(int pos, ll upd, Node *v, int l, int r) {
    if(r < pos || l > pos) return v;
    if(l == r) {
        return new Node(v->v + upd);
    }

    return new Node(update(pos, upd, v->l, EL), update(pos, upd, v->r, ER));
}

void solve() {
    cin >> n;
    F1(n) {
    	cin >> a[i];
    }

    roots[0] = build(INI);

    cin >> q;
    int nr = 0;

    F(q) {
        int op, b,c,d;
        cin >> op >> b >> c >> d;
        if(op == 1) {
            roots[++nr] = update(c, d, roots[b], INI);
        } else {
            cout << query(c, d, roots[b], INI).v << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

solve();
}
