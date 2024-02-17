// https://codeforces.com/contest/1083/problem/E

#include <bits/stdc++.h>
using namespace std;

typedef long long int T;
typedef long double ld;
#define CW -1
#define CCW 1

struct pt {
    T x ,y, z;
    pt(T x, T y, T z=0): x(x), y(y), z(z) {}
    
    pt operator+(pt o) { return pt(x+o.x, y+o.y);}
    pt operator-(pt o) { return pt(x-o.x, y-o.y);}
    
    T operator*(pt o) { return x*o.x + y*o.y; }
    T operator^(pt o) { return x*o.y - y*o.x;}
    
    bool operator<(pt o) const {
        if(x != o.x) return x< o.x;
        return y<o.y;        
    }
};

vector<pt> hull, nvecs;

bool dir_check(pt vec, pt p) {
    ld x1 = vec.x, y1 = vec.y, x2 = p.x, y2 = p.y;
    return (x1 * y2 - y1 * x2) < 0;
}

void add_line(T a, T b) {
    pt nw(a, b);
    while(!nvecs.empty() and dir_check(nvecs.back(), nw - hull.back())) {
        hull.pop_back();
        nvecs.pop_back();
    }
    
    pt t = nw - hull.back();
    if(!hull.empty()) nvecs.push_back(pt(-t.y, t.x));
    hull.push_back(nw);
}

T get(T x) {
    pt q(x, 1);
    int i = lower_bound(nvecs.begin(), nvecs.end(), q, [](pt a, pt q) {
        return (a^q) > 0;
    }) - nvecs.begin();
    
    return hull[i] * q;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    
    vector<pt> a;
    
    for(T i = 0, x, y, z; i < n; i++) {
        cin >> x >> y >> z;
        a.push_back(pt(x, y, z));
    }
    
    sort(a.begin(), a.end());
    
    vector<T> ans(n);
    ans[0] = a[0].x * a[0].y - a[0].z;
    hull.push_back(pt(a[0].x, -ans[0]));
    
    for(int i = 1; i < n; i++) {
        T q = get(a[i].y);
        ans[i] = a[i].x * a[i].y - a[i].z - q;
        add_line(a[i].x, -ans[i]);
    }
    
    //for(int i = 0; i < n; i++) cout << ans[i] << ' ';
    //cout << endl;
    
    cout << *max_element(ans.begin(), ans.end()) << endl;    
}
