// https://codeforces.com/problemset/problem/681/E
// Deu errado

#include <bits/stdc++.h>
using namespace std;

typedef double T;
typedef long long li;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
#define INV_PI 0.318309886183790671538

struct Circ {
	li x, y, r;
	Circ(li x=0, li y=0, li r=0): x(x), y(y), r(r) {}
};

struct pt {
	T x, y;
	bool beg;
	pt(T x=0, T y=0, bool beg=false): x(x), y(y), beg(beg) {}
	pt operator+(pt o) {return pt(x+o.x, y+o.y);}
	pt operator-(pt o) {return pt(x-o.x, y-o.y);}
	pt operator*(T a) {return pt(x*a, y*a);}
	pt operator/(T a) {return pt(x/a, y/a);}
	T operator*(pt o) {return x*o.x+y*o.y;}
	T operator^(pt o) {return x*o.y - y*o.x;}

	T norm2() {return x*x + y*y;}
	double norm() {return sqrt(norm2());}

	bool operator<(pt o) const {
		bool s1 = y < 0, s2 = o.y < 0;
		if(s1 != s2) return s2;
		if(s1) return x > o.x;
		return x < o.x;
	}
};

double ang(pt a, pt b) {
	if(abs(a*b) < EPS) return PI/2;
	if(abs(a.x+b.x) < EPS and abs(a.y+b.y) < EPS) return PI;
	return atan((b^a) / (a*b));
}

int circ_line_inter(double r, double a, double b, double c, pt& p1, pt& p2) {
	double dif = c*c-r*r*(a*a+b*b);
	if(dif > EPS) return 0;
	
	double x0 = -a*c/(a*a+b*b), y0=-b*c/(a*a+b*b);
	if(dif > -EPS) {
		p1.x = x0, p1.y = y0;
		return 1;	
	}
	
	double d = r*r - c*c/(a*a+b*b);
	double mult = sqrt(d/(a*a+b*b));
	p1.x = x0+b*mult;
	p2.x = x0 - b*mult;
	p1.y = y0-a*mult;
	p2.y = y0+a*mult;
	return 2;
}

int circ_circ_inter(li r1, li r2, li x2, li y2, pt& p1, pt& p2) {
	return circ_line_inter(r1, 2*x2, 2*y2, r2*r2 - x2*x2 - y2*y2 - r1*r1, p1, p2);
}

bool is_cw(pt a, pt b) {
	return (a^b) < EPS;
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
	
	vector<pt> shds;
	li R = v * t;
	
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
		
		double d = sqrt((double) x*x + y*y - r*r);
		
		if( d - R < EPS ) {
			pt v1(x, y);
			
			double vcos = d/v1.norm();
			double vsen = (double) r/v1.norm();
			
			v1 = v1 / v1.norm();
			pt v1n(-v1.y, v1.x);
			
			v1 = v1 * d * vcos;
			v1n = v1n * d * vsen;
			
			p1 = v1 + v1n;
			p2 = v1 - v1n;
		} else {
			int cnt = circ_circ_inter(R, r, x, y, p1, p2);
			if(cnt < 2) continue;
		}
		
		if(is_cw(p2, p1)) swap(p1, p2);
		p1.beg = true;
		p2.beg = false;
		
		shds.push_back(p1);
		shds.push_back(p2);
	}
	
	sort(shds.begin(), shds.end());
	
	int cnt_int = 0;
	double sa = 0;
	
	int pos, end_sec = -1;
	
	for(int j = 0; j < 2; j++) {
		int stop_pos = (end_sec == -1 ? shds.size() : end_sec); 
		for(int i = 0; i < stop_pos; i++) {
			//cout << shds[i].x << " " << shds[i].y << " " << (shds[i].beg ? "[" : "]") << endl;
			
			if(shds[i].beg) {
				cnt_int++;
				if(cnt_int == 1) pos = i;
			} else {
				if(cnt_int > 0) {
					cnt_int--;
					if(cnt_int == 0) { 
						double a = ang(shds[pos], shds[i]);
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
	
	double res = sa * INV_PI / 2;
	printf("%.8lf\n", res);
	
	return 0;
}