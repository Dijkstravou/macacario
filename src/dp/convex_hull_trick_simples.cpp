struct Line {
	li k, c, m;
	bool operator<(Line o) const { return k < o.k; }   
	bool operator<(li x) const { return m < x; } 
};

vector<Line> cht;

li _div(li a, li b) {  // divisao inteira com negativo
	return a/b - ((a^b) < 0 && a%b);
}
	
void add(li k, li c) {
	li m;
	while(!cht.empty() && (m = _div(c-cht.back().c, k-cht.back().k)) >= cht.back().m)
		cht.pop_back();
		
	if(cht.empty()) m = inf;
	cht.push_back({k, c, m});
}

li query(li x, int beg, int end) {
	assert(!cht.empty() && beg < end);
	auto l = *lower_bound(cht.begin()+beg, cht.begin()+end, -x);
	return l.k * x + l.c;
}
