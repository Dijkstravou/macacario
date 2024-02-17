// https://codeforces.com/problemset/problem/681/E
// Deu errado

#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef long long li;
const long double EPS = 1e-4;
#define PI 3.14159265358979323846
#define INV_PI 0.318309886183790671538

struct Circ {
	li x, y, r;
	Circ(li x=0, li y=0, li r=0): x(x), y(y), r(r) {}
};

struct pt {
	T x, y;
	pt(T x=0, T y=0): x(x), y(y) {}
	pt operator+(pt o) {return pt(x+o.x, y+o.y);}
	pt operator-(pt o) {return pt(x-o.x, y-o.y);}
	pt operator*(T a) {return pt(x*a, y*a);}
	pt operator/(T a) {return pt(x/a, y/a);}
	T operator*(pt o) {return x*o.x+y*o.y;}
	T operator^(pt o) {return x*o.y - y*o.x;}

	T norm2() {return x*x + y*y;}
	long double norm() {return sqrt(norm2());}
};

bool is_cw(pt a, pt b) {
	return (a^b) < EPS;
}

long double get_ang(li x, li y) {
	if(x == 0) return (y > 0) ? PI/2 : PI+PI/2;
	if(y == 0) return (x > 0) ? PI : 0;
	
	long double a = atan2(y, x);
	return PI-a;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	li x0, y0, v, t, n;
	cin >> x0 >> y0 >> v >> t >> n;
	
	vector<Circ> circs(n);
	for(int i = 0; i < n; i++) {
		cin >> circs[i].x >> circs[i].y >> circs[i].r;
		circs[i].x -= x0;
		circs[i].y -= y0;
	}
	
	li R = v * t;
	vector<pair<long double, bool>> angs;
	
	for(int i = 0; i < n; i++) {
		pt p1, p2;
		li x = circs[i].x, y = circs[i].y, r = circs[i].r;
		
		if(x == 0 and y == 0) {
			puts("1.0000");
			return 0;
		}
		
		if(x*x + y*y <= r*r) {
			puts("1.0000");
			return 0;
		}
		
		if(R == 0 or r == 0) continue;
		
		if(x*x+y*y-((long double) R+r)*(R+r) > -EPS) continue;
		
		long double d = sqrt(x*x + y*y - r*r);
		long double a;
		
		if( d - R < EPS ) {			
			// a = asin(r / sqrt(x*x+y*y));
			// a = acos(d / sqrt(x*x+y*y));
			a = atan2(r, d);
		} else {
			long double Rd = R;
			long double c = sqrt(x*x+y*y)/Rd + R/sqrt(x*x+y*y) - (r*r)/Rd/sqrt(x*x+y*y);
			c /= 2;
			
			// long double c = (x*x + y*y-r*r + (long double) R*R) / 2 / R / sqrt(x*x+y*y);
			a = acos(c);
		}
		
		long double mid = get_ang(x, y);
		//cout << "(" << x << ", " << y << ") = " << mid << endl;
		
		angs.push_back({mid-a, true});
		angs.push_back({mid+a, false});
	}
	
	sort(angs.begin(), angs.end());
	
	int cnt_int = 0;
	long double sa = 0;
	
	int pos, end_sec = -1;
	
	for(int j = 0; j < 2; j++) {
		int stop_pos = (end_sec == -1 ? angs.size() : end_sec); 
		for(int i = 0; i < stop_pos; i++) {
			//cout << angs[i].first << " " << (angs[i].second ? "[" : "]") << endl;
			
			if(angs[i].second) {
				cnt_int++;
				if(cnt_int == 1) pos = i;
			} else {
				if(cnt_int > 0) {
					cnt_int--;
					if(cnt_int == 0) { 
						long double a = angs[i].first - angs[pos].first;
						sa += a;
						//cout << a << endl;
				    }		
					if(end_sec == -1) end_sec = i;
				}
			}
		}
		
		if(cnt_int == 0) break;
	}
	
	//printf("SA = %.8lf\n", sa);
	
	long double res = sa * INV_PI / 2;
	printf("%.8Lf\n", res);
	
	return 0;
}