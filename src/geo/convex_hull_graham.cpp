#define CW -1
#define CCW 1

int orient(pt a, pt b, pt c) {
	T v = (b-a)^(c-a);
	if(v < 0) return CW;
	else if(v > 0) return CCW;
	return 0;
}

vector<pt> convex_hull(vector<pt>& a, bool usecol=false) {
	// Saida em sentido horario. usecol true = bota colineares no resultado
	// ALERTA: garanta que nao tem pontos repetidos no vetor
	// ALETA: a eh modificado (apenas ordenado)
	pt p0 = *min_element(all(a), [](pt a, pt b){
		return pt(a.y, a.x) < pt(b.y, b.x);
	});
	
	sort(all(a), [&p0](pt a, pt b) {
		int o = orient(p0, a, b);
		if(o == 0) return (a - p0).norm2() < (b - p0).norm2();
		return o == CW;
	});
	
	if(usecol) {
		int i = sza(a) - 2;
		while(i >= 0 && orient(p0, a[i], a.back()) == 0) i--;
		reverse(a.begin()+i+1, a.end());
	}
	
	vector<pt> st;
	for(int i = 0; i < sza(a); i++) {
		if(usecol)
			while(sza(st) > 1 && orient(st[sza(st)-2], st.back(), a[i]) == CCW)
				st.ppb();
		else
			while(sza(st) > 1 && orient(st[sza(st)-2], st.back(), a[i]) != CW)
				st.ppb();
		st.pb(a[i]);
	}
	
	return st;
}
