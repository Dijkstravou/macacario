// https://open.kattis.com/problems/parade

#include <bits/stdc++.h>
using namespace std;

typedef long long int T;
#define CW -1
#define CCW 1

struct pt {
    T x, y;
    
    pt(): x(0), y(0) {}
    pt(T x, T y): x(x), y(y) {}
    
    pt operator+(pt ot) { return pt(x+ot.x, y+ot.y); }
    pt operator-(pt ot) { return pt(x-ot.x, y-ot.y); }
    T operator*(pt ot) { return x*ot.x + y*ot.y; }
    T operator^(pt ot) { return x*ot.y - y*ot.x; }
    
    T norm2() { return x*x + y*y; }
    bool operator<(pt ot) const {
        if(x != ot.x) return x< ot.x;
        return y < ot.y;
    }
    bool operator==(pt ot) { return x == ot.x and y == ot.y; }
};

int orient(pt a, pt b, pt c) {
    T v = (b-a)^(c-a);
    if(v < 0) return CW;
    else if(v > 0) return CCW;
    return 0;
}

bool isor(int ot, pt a, pt b, pt c) {
    return orient(a, b, c) == ot;
}

void convex_hull(vector<pt>& a, vector<pt>& up, vector<pt>& down) {
    sort(a.begin(), a.end());
    pt p1 = a[0], p2 = a.back();
    
    up.push_back(p1);
    down.push_back(p1);
    
    for(int i = 1; i < a.size(); i++) {
        int o = CW;
        
        vector<pt>& t = up;
        if(i == a.size() - 1 or isor(o, p1, a[i], p2)) {
            while(t.size() > 1 and !isor(o, t[t.size()-2], t[t.size() - 1], a[i]))
                t.pop_back();    
            t.push_back(a[i]);
        }
        
        {
            o = CCW;
            vector<pt>& t = down;
            if(i == a.size() - 1 or isor(o, p1, a[i], p2)) {
                while(t.size() > 1 and !isor(o, t[t.size()-2], t[t.size() - 1], a[i]))
                    t.pop_back();    
                t.push_back(a[i]);
            }    
        }
    }
}

/*bool in_line(pt a, pt b, pt p) {  // a < b
    if(a.x == b.x) return p.x == a.x and a.y <= p.y and p.y <= b.y;
    return orient(a, b, p) == 0;
}*/

bool in_line(pt a, pt b, pt p) { 
    pt v1 = b-a, v2 = p-a;
    return (v1^v2) == 0 and v1*v2 > 0 and v2.norm2() < v1.norm2();
}

bool inside_hull(vector<pt>& up, vector<pt>& down, pt p, bool usecol) {    
    if(p.x < up[0].x or p.x > up[up.size() - 1].x) return false;
    
    T y = p.y;
    p.y = -1;
    
    int i = lower_bound(up.begin(), up.end(), p) - up.begin();
    int j = lower_bound(down.begin(), down.end(), p) - down.begin();
    p.y = y;
     
    //if(j+1 == down.size())
    if(i != 0) i--;
    if(j != 0 && (j+1 == down.size() || down[j].x != down[j+1].x || down[j].x != p.x)) j--;
    
    if(!usecol)
        assert(orient(up[i], up[i+1], p) != CCW or orient(down[j], down[j+1], p) != CW);
    
    //out << "j = " << j << " " << down[j].x << " " << down[j].y << " and " << down[j+1].x << " " << down[j+1].y << endl;
    bool res = orient(up[i], up[i+1], p) == CW and orient(down[j], down[j+1], p) == CCW;
    if(usecol)
        res = res or in_line(up[i], up[i+1], p) or in_line(down[j], down[j+1], p);
    return res;
}

int solve() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, s;
    vector<pt> nazi, tower;
    
    cin >> n;
    for(int i = 0, x, y; i < n; i++) {
        cin >> x >> y;
        nazi.push_back(pt(x, y));
    }
    
    cin >> s;
    for(int i = 0, x, y; i < s; i++) {
        cin >> x >> y;
        tower.push_back(pt(x, y));
    }
    
    vector<pt> up, down;
    convex_hull(nazi, up, down);
    
    int tot_hull = up.size() + down.size() - 2;
    if(tot_hull == 2) return 0;
    
    if(tot_hull == 3) {
        // Precisa considerar o caso em que tem colineares em + de 1 aresta, chato pra krl
        
        bool flag = false;
        pt p1 = up[0], p2 = up[up.size() - 1];        
        
        for(int i = 0; i < n; i++)
            if(inside_hull(up, down, nazi[i], false)) flag = true;
        
        if(!flag) return 0;
    }
    
    int cnt = 0;
    for(int i = 0; i < s; i++) 
        if(inside_hull(up, down, tower[i], true)) cnt++;
    
    return cnt;
}

int main() {
    cout << solve() << endl;
}
