// https://judge.yosupo.jp/problem/static_convex_hull
// PASSOU MAS CUIDADO PRA QUANDO E O MESMO PONTO VARIAS VEZES.
// (OU SEJA SAO DADOS N PONTOS PARA FAZER O CONVEX HULL, TODOS IGUAIS ENTRE SI)
// SE ISSO OCORRE, O CODIGO ORIGINAL DA LIB REPETE ESSE PONTO NO CONVEX HULL
// TRIVIAL CONSERTAR
// ESSE TESTE E APENAS PARA usecol=false

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

#define FF(i, n) for (int i = 0; i < (n); i++)
#define FF1(i, n) for (int i = 1; i <= (n); i++)
#define FFZ(i, v) FF(i, sza(v))
#define FFS(i, s, n) for (int i = s; i <= (n); i++)
#define FFD(i, n) for (int i = (n) - 1; i >= 0; i--)

#define F(n) FF(i, n)
#define F1(n) FF1(i, n)
#define FZ(v) FFZ(i, v)
#define FS(s, n) FFS(i, s, n)
#define FD(n) FFD(i, n)

template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& p) {
    return os << "(" << p.ff << ", " << p.ss << ")";
}
template <typename A> ostream& operator<<(ostream& os, const vector<A>& v) {
    os << "[";
    for (const auto& x : v)
        os << x << ", ";
    return os << "]";
}

#ifdef LOCAL
void dbg_out() { cerr << endl; }
template <typename H, typename... T> void dbg_out(H h, T... t) {
    cerr << " " << h;
    dbg_out(t...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

ll n, m, p, q, k;
ll a[maxn];

#define CW -1
#define CCW 1

typedef long long T;
typedef long double ld;

const ld EPS = 1e-7;

struct pt {
    T x, y;
    pt(T x = 0, T y = 0) : x(x), y(y) {}
    pt operator+(pt o) { return pt(x + o.x, y + o.y); }
    pt operator-(pt o) { return pt(x - o.x, y - o.y); }
    // pt operator*(T a) { return pt(a*x, a*y); }
    T operator*(pt o) { return x * o.x + y * o.y; }
    T operator^(pt o) { return x * o.y - y * o.x; }
    // pt operator^(pt o) { return pt(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x); }
    T norm2() { return x * x + y * y; }
    ld norm() { return sqrtl(norm2()); }
    bool operator<(pt o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

// Testes insuficientes
ld ang(pt a, pt b) { return atan2l(a ^ b, a * b); }

// Determinante (vetores nas linhas). Volume paralelepípedo.
// Usar versao 3d do cross product (^)
// T triple(pt a, pt b, pt c) { return a * (b^c); }

int orient(pt a, pt b, pt c) {
    T v = (b - a) ^ (c - a);
    if (v < 0)
        return CW;
    else if (v > 0)
        return CCW;
    return 0;
}

vector<pt> convex_hull(vector<pt>& a, bool usecol = false) {
    // Saida em sentido horario. usecol true = bota colineares no resultado
    // ALERTA: garanta que nao tem pontos repetidos no vetor
    // ALETA: a eh modificado (apenas ordenado)
    pt p0 = *min_element(all(a), [](pt a, pt b) { return pt(a.y, a.x) < pt(b.y, b.x); });

    sort(all(a), [&p0](pt a, pt b) {
        int o = orient(p0, a, b);
        if (o == 0) return (a - p0).norm2() < (b - p0).norm2();
        return o == CW;
    });

    if (usecol) {
        int i = sza(a) - 2;
        while (i >= 0 && orient(p0, a[i], a.back()) == 0)
            i--;
        reverse(a.begin() + i + 1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < sza(a); i++) {
        if (usecol)
            while (sza(st) > 1 && orient(st[sza(st) - 2], st.back(), a[i]) == CCW)
                st.ppb();
        else
            while (sza(st) > 1 && orient(st[sza(st) - 2], st.back(), a[i]) != CW)
                st.ppb();
        st.pb(a[i]);
    }

    if (sza(st) == 2 && (st[0] - st[1]).norm() < EPS) {
        st.erase(st.begin() + 1);
    }

    return st;
}

int t;

void solve() {
    cin >> n;
    if (!n) {
        cout << "0\n";
        return;
    }
    vector<pt> lula(n, pt());
    for (int i = 0; i < n; i++) {
        cin >> lula[i].x >> lula[i].y;
    }
    lula = convex_hull(lula);
    reverse(all(lula));
    cout << sza(lula) << "\n";
    for (int i = 0; i < sza(lula); i++) {
        cout << lula[i].x << " " << lula[i].y << "\n";
    }
}

int main() {
    cin >> t;
    while (t--)
        solve();
}