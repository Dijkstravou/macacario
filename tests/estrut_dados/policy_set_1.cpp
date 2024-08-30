// https://cses.fi/problemset/task/2163/
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

// Se nao der, tem esses arqui
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// Antes era pb_ds;
using namespace __gnu_pbds;

typedef tree<
	int,  //  Key type
	null_type,  // Mapped type.
	// null_mapped_type for older versions
	less<int>,  // Key comp function
	rb_tree_tag,  
	tree_order_statistics_node_update
> ordered_set;

// iterator find_by_order(int pos)
// iterator order_of_key(Key key)

ordered_set s;

void solve() {
    cin >> n >> k;
	F1(n) s.insert(i);

	int cur = 0;
	F(n) {
		cur = (cur + k) % (n-i);
		auto it =s.find_by_order(cur); 
		cout << *it << ' ';

		s.erase(it);
	}
	cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

	solve();}
