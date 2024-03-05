struct Line {
	ll k, c, m;
	bool operator<(Line o) const { return k < o.k; }   
	bool operator<(ll x) const { return m < x; } 
};

vector<Line> cht;

ll _div(ll a, ll b) {  // divisao inteira com negativo
	return a/b - ((a^b) < 0 && a%b);
}
	
void add(ll k, ll c) {
	ll m;
	while(!cht.empty() && (m = _div(c-cht.back().c, k-cht.back().k)) >= cht.back().m)
		cht.ppb();
		
	if(cht.empty()) m = inf;
	cht.pb({k, c, m});
}

ll query(ll x, int beg, int end) {
	assert(!cht.empty() && beg < end);
	auto l = *lower_bound(cht.begin()+beg, cht.begin()+end, -x);
	return l.k * x + l.c;
}
