//https://codeforces.com/gym/104945/problem/E
//Implementação overkill só pra testar

#include <bits/stdc++.h>

using namespace std;

typedef long long li;
typedef pair<li, li> pii;

#define DBG(x) {cout << #x": " << x << " "; }

const li MAXN = 1e5 + 10;
const li inf = 1e9;

struct Frac {
	li p, q;
	
	Frac(): p(0), q(1) {}
	Frac(li _p, li _q=1): p(_p), q(_q) {
		assert(q!=0);
		if(q < 0) { p = -p, q = -q; }

		reduce();
	}
	
	void reduce() {
		li g = __gcd(abs(p), q);
		p /= g, q /= g;
	}
	
	Frac operator+(Frac ot) const {
		return Frac(p*ot.q + ot.p*q, q*ot.q);
	}
	
	Frac operator-(Frac ot) const {
		return Frac(p*ot.q - ot.p*q, q*ot.q);
	}
	
	Frac operator*(Frac ot) const {
		return Frac(p*ot.p, q*ot.q);
	}
	
	bool operator<(Frac ot) const {
		return (*this - ot).p < 0;
	}
	
	bool operator>(Frac ot) const {
		return ot < *this;
	}
	
	Frac operator-() const {
		return Frac(-p, q);
	}
};

ostream& operator<<(ostream& os, Frac f) {
	return os << f.p << "/" << f.q;
}

li n;
li a[MAXN];

struct Line {
	li k, c, m;
	li slope;
	bool operator<(Line o) const { return k < o.k; }   
	bool operator>(Line o) const { return o<*this; }
	bool operator<(Frac x) const { return m*x.q < x.p; } 
};

vector<Line> cht;

li _div(li a, li b) {  // divisao inteira com negativo
	return a/b - ((a^b) < 0 && a%b);
}
	
void add(li k, li c, li slope) {
	li m;
	while(!cht.empty() && (m = _div(c-cht.back().c, k-cht.back().k)) >= cht.back().m)
		cht.pop_back();
		
	if(cht.empty()) m = inf;
	cht.push_back({k, c, m, slope});
}

Frac query(Frac x, int beg, int end) {
	assert(!cht.empty() && beg < end);
	auto l = *lower_bound(cht.begin()+beg, cht.begin()+end, -x);
	return Frac(l.k) * x + Frac(l.c);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	Frac res;
	
	for(int i = 1; i < n; i++) {
		li slope = a[i+1] - a[i];
		if(slope > 0) {
			if(cht.empty()) continue;
			// max_pt{i + (pt.y - a[i]) / slope - pt.x}
			// i - a[i]/slope + max_pt{pt.y / slope - pt.x}
			// i - a[i]/slope - min_pt{-pt.y / slope + pt.x}

			Frac qs(1, slope);
			int end = lower_bound(cht.begin(), cht.end(), Line{-a[i], 0}) - cht.begin();
			int beg = lower_bound(cht.begin(), cht.end(), Line{-a[i+1], 0}) - cht.begin();

			if(beg < end) {
				Frac resq = query(qs, beg, end);
				Frac f = Frac(i) - Frac(a[i], slope) - resq;
				res = max(res, f);
			}
			
			if(beg > 0) {
				li y1 = -cht[beg-1].k, s1 = cht[beg-1].slope, x1 = cht[beg-1].c;
				
				// slope*x + a[i] = y1
				// x = (y1 - a[i]) / slope
				
				Frac f(a[i+1] - y1, s1);
				res = max(res, Frac(i+1-x1, 1) - f);
			}
		} else {
			while(!cht.empty() && -cht.back().k <= a[i])
				cht.pop_back();
			add(-a[i], i, slope);
		}
	}

	if(res.q == 1) cout << res.p << '\n';
	else cout << res.p << "/" << res.q << "\n";
}
