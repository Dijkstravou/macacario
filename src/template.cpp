
//https://codeforces.com/blog/entry/76531
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;

const ll maxn = 2e5 + 10;
const ll inf = LLONG_MAX;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

#define pb push_back
#define ppb pop_back 
#define ff first
#define ss second 
#define sza(x) ((int)(x).size())
#define all(a) (a).begin(), (a).end()

#ifdef LOCAL
void dbg_out() { cerr << endl; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << ' ' << h; dbg_out(t...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

ll n, m, p, q, k;
ll a[maxn];

void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;

    for(int i = 1; i <= t; i++) solve();
}
