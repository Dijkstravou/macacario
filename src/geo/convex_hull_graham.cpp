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
	pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b){
		return pt(a.y, a.x) < pt(b.y, b.x);
	});
	
	sort(a.begin(), a.end(), [&p0](pt a, pt b) {
		int o = orient(p0, a, b);
		if(o == 0) return (a - p0).norm2() < (b - p0).norm2();
		return o == CW;
	});
	
	if(usecol) {
		int i = a.size() - 2;
		while(i >= 0 && orient(p0, a[i], a.back()) == 0) i--;
		reverse(a.begin()+i+1, a.end());
	}
	
	vector<pt> st;
	for(int i = 0; i < a.size(); i++) {
		if(usecol)
			while(st.size() > 1 && orient(st[st.size()-2], st.back(), a[i]) == CCW)
				st.pop_back();
		else
			while(st.size() > 1 && orient(st[st.size()-2], st.back(), a[i]) != CW)
				st.pop_back();
		st.push_back(a[i]);
	}
	
	return st;
}
