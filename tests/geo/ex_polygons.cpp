// https://codeforces.com/contest/166/problem/B

#include <bits/stdc++.h>
using namespace std;

#define CW -1
#define CCW 1
typedef long long int T;

#define QNO {cout << "NO" << endl; return 0;}

struct pt {
    T x, y;
    pt(T x, T y) : x(x), y(y) {
        
    }
    
    pt operator+(pt o) { return pt(x+o.x, y+o.y);}
    pt operator-(pt o) { return pt(x-o.x, y-o.y);}
    T operator^(pt o) { return x*o.y - y*o.x;}
    
    bool operator<(pt o) {
        if(x != o.x) return x< o.x;
        return y < o.y;            
    }
    
    T norm2() { return x*x + y*y;}
};

int orient(pt a, pt b, pt c) {
    T v = (b-a) ^ (c-a);
    if(v < 0) return CW;
    else if(v> 0) return CCW;
    return 0;
}

vector<pt> convex_hull(vector<pt>& a) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return pt(a.y, a.x) < pt(b.y, b.x);
    });
    
    sort(a.begin(), a.end(), [&p0](pt a, pt b) {
        int o = orient(p0, a, b);
        if(o == 0) return (a - p0).norm2() < (b - p0).norm2();
        return o == CW;
    });
    
    vector<pt> st;
    for(int i = 0; i < a.size(); i++) {
        while(st.size() > 1 and orient(st[st.size()-2], st[st.size()-1], a[i]) != CW)
            st.pop_back();
        st.push_back(a[i]);
    }
    
    return st;
}

bool isor(int o, pt a, pt b, pt c, bool usecol) {
    int ot= orient(a, b, c);
    return o == ot or (usecol and ot == 0);
}

bool in_triangle(pt p0, pt a, pt b, pt p, bool u1, bool u2) {
    return isor(CW, p0, a, p, u1) and isor(CCW, p0, b, p, u2) and isor(CW, a, b, p, false);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m;
    cin >> n;
    
    vector<pt> a, b;
    for(int i = 0; i < n; i++) 
    {
        int x, y;
        cin >> x >> y;
        a.push_back(pt(x, y));
        
    }
    
    cin >> m;
    for(int i = 0; i < m; i++) 
    {
        int x, y;
        cin >> x >> y;
        b.push_back(pt(x, y));
    }
    
    a = convex_hull(a);
    
    pt p0 = a[0];
    sort(b.begin(), b.end(), [&p0](pt a, pt b) {
        int o = orient(p0, a, b);
        if(o == 0) return (a - p0).norm2() < (b - p0).norm2();
        return o == CW;
    });
    
    for(int i = 0, j = 1; i < m; i++) {
        while(j+1<n and orient(p0, a[j+1], b[i]) == CW) j++;
        if(j+1 == n) QNO
        
        if(!in_triangle(p0, a[j], a[j+1], b[i], j!=1, j+2!=n)) QNO
    }
    
    cout << "YES" << endl;
}
