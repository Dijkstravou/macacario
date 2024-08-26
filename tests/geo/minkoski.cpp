// https://codeforces.com/problemset/problem/87/E

// https://codeforces.com/problemsets/acmsguru/problem/99999/253

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

ll m, p, q, k;
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
    long long cross(pt p) { return x * p.y - y * p.x; }
    long long cross(pt a, pt b) { return (a - *this).cross(b - *this); }
    bool operator<(pt o) {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

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

bool lexComp(const pt& l, const pt& r) { return l.x < r.x || (l.x == r.x && l.y < r.y); }

int sgn(long long val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }

vector<pt> seq;
pt translation;
int n;
bool pointInTriangle(pt a, pt b, pt c, pt point) {
    long long s1 = abs(a.cross(b, c));
    long long s2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return s1 == s2;
}

void prepare(vector<pt>& points) {
    n = points.size();
    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (lexComp(points[i], points[pos])) pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());

    n--;
    seq.resize(n);
    for (int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
    translation = points[0];
}

bool pointInConvexPolygon(pt point) {
    point = point - translation;
    if (seq[0].cross(point) != 0 && sgn(seq[0].cross(point)) != sgn(seq[0].cross(seq[n - 1])))
        return false;
    if (seq[n - 1].cross(point) != 0 &&
        sgn(seq[n - 1].cross(point)) != sgn(seq[n - 1].cross(seq[0])))
        return false;

    if (seq[0].cross(point) == 0) return seq[0].norm2() >= point.norm2();

    int l = 0, r = n - 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        int pos = mid;
        if (seq[pos].cross(point) >= 0)
            l = mid;
        else
            r = mid;
    }
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], pt(0, 0), point);
}

void reorder_polygon(vector<pt>& P) {
    size_t pos = 0;
    for (size_t i = 1; i < P.size(); i++) {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q) {
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<pt> result;
    size_t i = 0, j = 0;
    while (i < P.size() - 2 || j < Q.size() - 2) {
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if (cross >= 0 && i < P.size() - 2) ++i;
        if (cross <= 0 && j < Q.size() - 2) ++j;
    }
    return result;
}

void solve() {
    cin >> n >> m >> k;
    vector<pt> points;
    for (int i = 0; i < n; i++) {
        points.push_back(pt(0, 0));
        cin >> points[sza(points) - 1].x >> points[sza(points) - 1].y;
    }
    prepare(points);
    pt p(0, 0);
    int score = 0;
    for (int i = 0; i < m; i++) {
        cin >> p.x >> p.y;
        bool b = pointInConvexPolygon(p);
        score += b;
    }

    if (score >= k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int n1, n2, n3;
vector<pt> c1, c2, c3;

void le_cidade(int& v, vector<pt>& vec) {
    cin >> v;
    for (int i = 0; i < v; i++) {
        vec.push_back(pt(0, 0));
        cin >> vec[sza(vec) - 1].x >> vec[sza(vec) - 1].y;
    }
}

int main() {
    vector<pt> soma12;
    vector<pt> soma123;
    le_cidade(n1, c1);
    le_cidade(n2, c2);
    le_cidade(n3, c3);

    soma12 = minkowski(c1, c2);
    soma123 = minkowski(soma12, c3);

    int m;
    prepare(soma123);
    cin >> m;
    for (int i = 0; i < m; i++) {
        pt p(0, 0);
        cin >> p.x >> p.y;
        p.x *= 3;
        p.y *= 3;
        if (pointInConvexPolygon(p)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}