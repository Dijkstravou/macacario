

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld EPS = 1e-7;

typedef long long int T;
struct pt {
    T x, y;
    pt(T x = 0, T y = 0) : x(x), y(y) {}
    pt operator+(pt o) { return pt(x + o.x, y + o.y); }
    pt operator-(pt o) { return pt(x - o.x, y - o.y); }
    pt operator*(T a) { return pt(a * x, a * y); }
    T operator*(pt o) { return x * o.x + y * o.y; }
    T operator^(pt o) { return x * o.y - y * o.x; }
    // bool operator==(pt p) { return x == p.x && y == p.y; }
    bool operator==(pt p) { return abs(x - p.x) < EPS && abs(y - p.y) < EPS; }
    // pt operator^(pt o) { return pt(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x); }
    T norm2() { return x * x + y * y; }
    ld norm() { return sqrtl(norm2()); }
    bool operator<(pt o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    friend ostream& operator<<(ostream& os, const pt& p) {
        os << p.x << " " << p.y;
        return os;
    }
};

// Testes insuficientes
ld ang(pt a, pt b) { return atan2l(a ^ b, a * b); }

// Determinante (vetores nas linhas). Volume paralelepípedo.
// Usar versao 3d do cross product (^)
// T triple(pt a, pt b, pt c) { return a * (b^c); }

pt intersect(pt a1, pt d1, pt a2, pt d2) { return a1 + (d1 * (((a2 - a1) ^ d2) / (d1 ^ d2))); }

void le(pt& p) { cin >> p.x >> p.y; }

const ld PI = acosl(-1);

bool opposite_vecs(pt v1, pt v2) { return abs(abs(ang(v1, v2)) - PI) < EPS; }

bool checa_ponto_segmento(pt ext1, pt ext2, pt testa) {
    if (ext1 == testa || ext2 == testa) return true;
    if (opposite_vecs(testa - ext1, testa - ext2)) return true;
    return false;
}

bool checa_intersec_segmento(pt p1, pt p2, pt p3, pt p4) {
    pt d1 = p1 - p2;
    pt d2 = p3 - p4;
    if (abs(d1 ^ d2) < EPS) {
        if (checa_ponto_segmento(p1, p2, p3) || checa_ponto_segmento(p1, p2, p4) ||
            checa_ponto_segmento(p3, p4, p1) || checa_ponto_segmento(p3, p4, p2)) {
            return true;
        }
        return false;
    }
    pt inter = intersect(p1, d1, p3, d2);
    if (checa_ponto_segmento(p1, p2, inter) && checa_ponto_segmento(p3, p4, inter)) {
        return true;
    }
    return false;
}

void solve() {
    pt ps[4];
    for (int i = 0; i < 4; i++)
        le(ps[i]);
    if (checa_intersec_segmento(ps[0], ps[1], ps[2], ps[3])) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

ld ang2(pt ponto) {
    ld xcoord = ponto.x / ponto.norm();
    return acos(xcoord);
}

T signed_area_parallelogram(pt p1, pt p2, pt p3) { return (p2 - p1) ^ (p3 - p2); }

double triangle_area(pt p1, pt p2, pt p3) {
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}

ld dist_seg(pt p, pt ext1, pt ext2) {
    ld x = p.x;
    ld y = p.y;
    ld px = ext1.x;
    ld py = ext1.y;
    ld qx = ext2.x;
    ld qy = ext2.y;
    ld a = py - qy;
    ld b = qx - px;
    ld c = -a * px - b * py;
    ld naretax, naretay;
    if (abs(a) < EPS) {
        naretax = 0;
        naretay = -c / b;
    } else {
        naretay = 0;
        naretax = -c / a;
    }
    pt q(naretax, naretay);
    ld t = ((q - pt(x, y)) * pt(a, b)) / (a * a + b * b);
    pt resp = pt(x, y) + (pt(a, b) * t);

    if (checa_ponto_segmento(pt(px, py), pt(qx, qy), resp)) {
        return (resp - pt(x, y)).norm();
    } else {
        ld dp = (pt(x, y) - pt(px, py)).norm();
        ld dq = (pt(x, y) - pt(qx, qy)).norm();
        return min(dp, dq);
    }
}

int main() {
    freopen("intersec1.in", "r", stdin);
    freopen("intersec1.out", "w", stdout);
    ld a1, b1, c1, a2, b2, c2;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    // tie(a1, b1) = make_tuple(-b1, a1);
    // tie(a2, b2) = make_tuple(-b2, a2);

    ld det = a1 * b2 - a2 * b1;
    ld numx = -c1 * b2 + c2 * b1;
    ld numy = -c2 * a1 + a2 * c1;
    ld x = (ld)numx / det;
    ld y = (ld)numy / det;
    printf("%.10Lf %.10Lf\n", x, y);
}