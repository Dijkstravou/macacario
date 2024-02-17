#include <bits/stdc++.h>
using namespace std;

#define CW -1
#define CCW 1

typedef long long int T;
struct pt {
    T x, y;
    pt(T x, T y): x(x), y(y) {}
    
    pt operator+(pt o) { return pt(x+o.x, y+o.y);}
    pt operator-(pt o) { return pt(x-o.x, y-o.y);}
    T operator^(pt o) { return x*o.y - y*o.x;}
    
    T norm2() { return x*x + y*y;}
    
    bool operator<(pt o) {
        if(x != o.x) return x< o.x;
        return y < o.y;    
    }
};

int orient(pt a, pt b, pt c) {
    T v = (b-a)^(c-a);
    if(v < 0) return CW;
    else if(v > 0)   return CCW;
    return 0;
}

bool isor(int ot, pt a, pt b, pt c) {
    int o = orient(a, b, c);
    return o == ot;
}

vector<pt> convex_hull(vector<pt> &a) {
    sort(a.begin(), a.end());
    
    pt p1 = a[0], p2 = a.back();
    vector<pt> up = {p1};
    
    for(int i = 1; i < a.size(); i++) {
        int o= CW;
        vector<pt>& t = up;
        
        if(i == a.size() - 1 || isor(o, p1, a[i], p2)) {
            while(t.size() > 1 and !isor(o, t[t.size() - 2], t[t.size() - 1], a[i]))
                t.pop_back();
            t.push_back(a[i]);
        }
    }
    
    return up;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    vector<pt> a;
    
    cin >> n;
    for(int i =0 ; i < n; i++) {
        T x, y;
        cin >> x >> y;
        a.push_back(pt(x, y - x*x));
    }
    
    vector<pt> up = convex_hull(a);
    int cnt = up.size() - 1;
    if(up[0].x == up[1].x) cnt--;
    
    cout << cnt << endl;
}
