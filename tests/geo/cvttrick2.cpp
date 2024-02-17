// https://codeforces.com/gym/103536/problem/B

#include <bits/stdc++.h>
using namespace std;

typedef long long int T;
#define CW -1
#define CCW 1

struct pt {
    T x, y;
    pt(T x, T y) : x(x), y(y) {}
    
    pt operator+(pt o) {return pt(x+o.x, y+o.y);}
    pt operator-(pt o) {return pt(x-o.x, y-o.y);}
    
    T operator*(pt o) {return x*o.x + y*o.y;}
    T operator^(pt o) {return x*o.y - y*o.x;}
    
    bool operator<(pt o) {
        if(x != o.x) return x< o.x;
        return y < o.y;    
    }
};

vector<pt> hull, nvecs;

void add_line( T a, T b) {
    pt nw(a, b);
    while(!nvecs.empty() and (nvecs.back() * (nw - hull.back())) < 0) {
        hull.pop_back();
        nvecs.pop_back();
    }
    
    if(!hull.empty()) {
        pt t = nw - hull.back();
        nvecs.push_back(pt(-t.y, t.x));
    }
    hull.push_back(nw);  
}

T get(T x) {
    pt q(x, 1);
    int i= lower_bound(nvecs.begin(), nvecs.end(), q, [](pt a, pt q){
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
    for(int i = 0, x, y; i < n; i++) {
        cin >> x >> y;
        a.push_back(pt(x, y));
    }
    
    sort(a.begin(), a.end());
    vector<pt> b;
    
    for(int i = 0; i < a.size(); i++) {
        pt p = a[i];
        while(!b.empty() and b.back().y <= p.y) 
            b.pop_back();
        b.push_back(p);
    }
    
    
    n = b.size();
    
    vector<T> ans(n);
    
    for(int i = 0; i < n; i++) {
        T v = b[i].x * b[i].y;
        T ant = (i == 0) ? 0 : ans[i-1];
        
        //cout << "i = " << i << " pt = (" << b[i].x << " " << b[i].y << ")" << endl;
        
        v += ant;
        if(i > 0) {
            T junto = get(-b[i].x);
            //cout << "Junto = " << junto << endl;
            v = min(v, junto);
        }
        
        ans[i] = v;
        add_line(-b[i].y, ant);
    }
    
    cout << ans[n-1] << endl;
}
