#define CW -1
#define CCW 1

int orient(pt a, pt b, pt c) {
	T v = (b-a)^(c-a);
	if(v < 0) return CW;
	else if(v > 0) return CCW;
	return 0;
}

bool isor(int ot, pt a, pt b, pt c, bool usecol) {
	int o = orient(a, b, c);
	return o == ot or (usecol && o == 0);
}

vector<pt> convex_hull(vector<pt>& a, bool usecol=false) {
	// Saida em sentido horario. usecol true = bota colineares no resultado
	// ALERTA: garanta que nao tem pontos repetidos no vetor
	// ALERTA: a eh modificado (ordenado)
	if(a.size() == 1) return a;
	
	sort(a.begin(), a.end());
	pt p1 = a[0], p2 = a.back();
	vector<pt> up = {p1}, down = {p1};
	
	for(int i = 1; i < a.size(); i++) {
		int o = CW;
		
		vector<pt>& t = up;
		if(i == a.size() - 1 or isor(o, p1, a[i], p2, usecol)) {
			while(t.size() > 1 and !isor(o, t[t.size()-2], t[t.size()-1], a[i], usecol))
				t.pop_back();
			t.push_back(a[i]);
		}
		
		{ // NAO TIRAR ESSA CHAVE
			o = CCW;
			vector<pt>& t = down;
			if(i == a.size() - 1 or isor(o, p1, a[i], p2, usecol)) {
				while(t.size() > 1 and !isor(o, t[t.size()-2], t[t.size()-1], a[i], usecol))
					t.pop_back();
				t.push_back(a[i]);
			}
		}
	}
	
	if(usecol and up.size() == a.size()) {
		reverse(a.begin(), a.end());
		return a;
	}
	
	for(int i = down.size() - 2; i > 0; i--) up.push_back(down[i]);
	return up;
}