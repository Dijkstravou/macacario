#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld EPS = 1e-7;

typedef ld T;
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

int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}