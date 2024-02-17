// https://codeforces.com/contest/319/problem/C

#include <bits/stdc++.h>
using namespace std;

typedef long long int li;

struct Line {
    mutable li k, c, m;
    bool operator<(Line o) const { return k < o.k; }   
    bool operator<(li x) const { return m < x; } 
};

struct LineCont : multiset<Line, less<>> {
    const li inf = LLONG_MAX;
    li div(li a, li b) {  // divisao inteira com negativo
        return a/b - ((a^b) < 0 && a%b);
    }
    bool ncon(iterator a, iterator b) {  // not convex
        if(b == end()) { a->m = inf; return 0; }
        if(a->k == b->k) a->m = (a->c > b->c) ? -inf : inf;
        else a->m = div(b->c - a->c, b->k - a->k);
        return a->m >= b->m;
    }
    void add(li k, li c) {
        auto z = insert({k, c, 0}), y = z++, x = y;
        while(ncon(y, z)) z = erase(z);
        if(x != begin() && ncon(--x, y)) ncon(x, erase(y));
        while((y = x) != begin() && (--x)->m >= y->m) 
            ncon(x, erase(y));
    }
    li query(li x) {
        assert(!empty());
        auto l = *lower_bound(-x);
        return l.k * x + l.c;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    
    vector<li> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    
    LineCont lines;
    lines.add(b[0], 0);
    
    li v = 0;
    for(int i = 1; i < n; i++) {
        v = lines.query(a[i]);
        lines.add(b[i], v);
    }
    
    cout << v << endl;
}
