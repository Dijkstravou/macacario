struct Line {
	mutable ll k, c, m;
	bool operator<(Line o) const { return k < o.k; }   
	bool operator<(ll x) const { return m < x; } 
};

struct LineCont : multiset<Line, less<>> {
	ll div(ll a, ll b) {  // divisao inteira com negativo
		return a/b - ((a^b) < 0 && a%b);
	}
	bool ncon(iterator a, iterator b) {  // not convex
		if(b == end()) { a->m = inf; return 0; }
		if(a->k == b->k) a->m = (a->c > b->c) ? -inf : inf;
		else a->m = div(b->c - a->c, b->k - a->k);
		return a->m >= b->m;
	}
	void add(ll k, ll c) {
		auto z = insert({k, c, 0}), y = z++, x = y;
		while(ncon(y, z)) z = erase(z);
		if(x != begin() && ncon(--x, y)) ncon(x, erase(y));
		while((y = x) != begin() && (--x)->m >= y->m) 
			ncon(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(-x);
		return l.k * x + l.c;
	}
};