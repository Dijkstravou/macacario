// por enquanto desisti, mto trabalho rs

/**
 * Author: Philippe Legault
 * Date: 2016
 * License: MIT
 * Source: https://github.com/Bathlamos/delaunay-triangulation/
 * Description: Fast Delaunay triangulation.
 * Each circumcircle contains none of the input points.
 * There must be no duplicate points.
 * If all points are on a line, no triangles will be returned.
 * Should work for doubles as well, though there may be precision issues in 'circ'.
 * Returns triangles in order \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\}, all counter-clockwise.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#include <bits/stdc++.h>
using namespace std;

// #include "Point.h"

/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const { return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    friend ostream& operator<<(ostream& os, P p) { return os << "(" << p.x << "," << p.y << ")"; }
};

typedef long long int ll;
typedef Point<ll> P;
typedef struct Quad* Q;
typedef __int128_t lll;      // (can be ll if coords are < 2e4)
P arb(LLONG_MAX, LLONG_MAX); // not equal to any other point

struct Quad {
    Q rot, o;
    P p = arb;
    bool mark;
    P& F() { return r()->p; }
    Q& r() { return rot->rot; }
    Q prev() { return rot->o->rot; }
    Q next() { return r()->prev(); }
}* H;

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
    lll p2 = p.dist2(), A = a.dist2() - p2, B = b.dist2() - p2, C = c.dist2() - p2;
    return p.cross(a, b) * C + p.cross(b, c) * A + p.cross(c, a) * B > 0;
}
Q makeEdge(P orig, P dest) {
    Q r = H ? H : new Quad{new Quad{new Quad{new Quad{0}}}};
    H = r->o;
    r->r()->r() = r;
    for (int i = 0; i < 4; i++)
        r = r->rot, r->p = arb, r->o = i & 1 ? r : r->r();
    r->p = orig;
    r->F() = dest;
    return r;
}
void splice(Q a, Q b) {
    swap(a->o->rot->o, b->o->rot->o);
    swap(a->o, b->o);
}
Q connect(Q a, Q b) {
    Q q = makeEdge(a->F(), b->p);
    splice(q, a->next());
    splice(q->r(), b);
    return q;
}

pair<Q, Q> rec(const vector<P>& s) {
    if (s.size() <= 3) {
        Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
        if (s.size() == 2) return {a, a->r()};
        splice(a->r(), b);
        auto side = s[0].cross(s[1], s[2]);
        Q c = side ? connect(b, a) : 0;
        return {side < 0 ? c->r() : a, side < 0 ? c : b->r()};
    }

#define H(e) e->F(), e->p
#define valid(e) (e->F().cross(H(base)) > 0)
    Q A, B, ra, rb;
    int half = s.size() / 2;
    tie(ra, A) = rec({begin(s), end(s) - half});
    tie(B, rb) = rec({s.size() - half + begin(s), end(s)});
    while ((B->p.cross(H(A)) < 0 && (A = A->next())) || (A->p.cross(H(B)) > 0 && (B = B->r()->o)))
        ;
    Q base = connect(B->r(), A);
    if (A->p == ra->p) ra = base->r();
    if (B->p == rb->p) rb = base;

#define DEL(e, init, dir)                                                                          \
    Q e = init->dir;                                                                               \
    if (valid(e))                                                                                  \
        while (circ(e->dir->F(), H(base), e->F())) {                                               \
            Q t = e->dir;                                                                          \
            splice(e, e->prev());                                                                  \
            splice(e->r(), e->r()->prev());                                                        \
            e->o = H;                                                                              \
            H = e;                                                                                 \
            e = t;                                                                                 \
        }
    for (;;) {
        DEL(LC, base->r(), o);
        DEL(RC, base, prev());
        if (!valid(LC) && !valid(RC)) break;
        if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
            base = connect(RC, base->r());
        else
            base = connect(base->r(), LC->r());
    }
    return {ra, rb};
}

vector<P> triangulate(vector<P> pts) {
    sort(pts.begin(), pts.end());
    assert(unique(pts.begin(), pts.end()) == pts.end());
    if (pts.size() < 2) return {};
    Q e = rec(pts).first;
    vector<Q> q = {e};
    int qi = 0;
    while (e->o->F().cross(e->F(), e->p) < 0)
        e = e->o;
#define ADD                                                                                        \
    {                                                                                              \
        Q c = e;                                                                                   \
        do {                                                                                       \
            c->mark = 1;                                                                           \
            pts.push_back(c->p);                                                                   \
            q.push_back(c->r());                                                                   \
            c = c->next();                                                                         \
        } while (c != e);                                                                          \
    }
    ADD;
    pts.clear();
    while (qi < q.size())
        if (!(e = q[qi++])->mark) ADD;
    return pts;
}

Point<ll> read_pt() {
    Point<ll> pt;
    cin >> pt.x >> pt.y;
    return pt;
}

void display_pt(Point<ll> p) { cout << p.x << " " << p.y << "\n"; }

Point<ll> rect[4];
int n;

double max_dist_to_rect(Point<ll> p) {
    double ans = (p - rect[0]).dist();
    for (int i = 1; i < 4; i++)
        ans = max(ans, (p - rect[i]).dist());
    return ans;
}

Point<double> from_ll(Point<ll> pt) {
    Point<double> ans;
    ans.x = pt.x;
    ans.y = pt.y;
    return ans;
}

/*
pt bary(pt A, pt B, pt C, ld a, ld b, ld c) { return (A * a + B * b + C * c) / (a + b + c); }

pt centroid(pt A, pt B, pt C) {
    // geometric center of mass
    return bary(A, B, C, 1, 1, 1);
}

pt circumcenter(pt A, pt B, pt C) {
    // intersection of perpendicular bisectors
    ld a = norm(B - C), b = norm(C - A), c = norm(A - B);
    return bary(A, B, C, a * (b + c - a), b * (c + a - b), c * (a + b - c));
}
*/
int main() {
    for (int i = 0; i < 4; i++)
        rect[i] = read_pt();
    cin >> n;
    vector<Point<ll>> pts, actual_pts;
    for (int i = 0; i < n; i++)
        pts.push_back(read_pt());
    sort(pts.begin(), pts.end());
    for (int i = 1; i < n; i++) {
        if (pts[i].x != pts[i - 1].x && pts[i].y != pts[i - 1].y) {
            actual_pts.push_back(pts[i - 1]);
        }
    }
    actual_pts.push_back(pts[pts.size() - 1]);
    n = actual_pts.size();
    vector<Point<ll>> with_rect = actual_pts;
    vector<Point<ll>> tri = triangulate(actual_pts);
    map<Point<ll>, double> dist;
    for (int i = 0; i < n; i++)
        dist[actual_pts[i]] = max_dist_to_rect(actual_pts[i]);
    if (tri.empty()) {
        // all collinear
        for (int i = 0; i < n; i++) {
        }
    }
    for (int i = 0; i < tri.size(); i += 3) {
        for (int j = 0; j < 3; j++)
            display_pt(tri[i + j]);
        Point<double> A, B, C;
        A = from_ll(tri[i]);
        B = from_ll(tri[i + 1]);
        C = from_ll(tri[i + 2]);
    }
}