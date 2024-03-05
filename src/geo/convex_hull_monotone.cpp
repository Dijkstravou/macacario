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
	return o == ot || (usecol && o == 0);
}

vector<pt> convex_hull(vector<pt>& a, bool usecol=false) {
	// Saida em sentido horario. usecol true = bota colineares no resultado
	// ALERTA: garanta que nao tem pontos repetidos no vetor
	// ALERTA: a eh modificado (ordenado)
	if(sza(a) == 1) return a;
	
	sort(all(a));
	pt p1 = a[0], p2 = a.back();
	vector<pt> up = {p1}, down = {p1};
	
	for(int i = 1; i < sza(a); i++) {
		int o = CW;
		
		vector<pt>& t = up;
		if(i == sza(a) - 1 || isor(o, p1, a[i], p2, usecol)) {
			while(sza(t) > 1 && !isor(o, t[sza(t)-2], t.back(), a[i], usecol))
				t.ppb();
			t.pb(a[i]);
		}
		
		{ // NAO TIRAR ESSA CHAVE
			o = CCW;
			vector<pt>& t = down;
			if(i == sza(a) - 1 || isor(o, p1, a[i], p2, usecol)) {
				while(sza(t) > 1 && !isor(o, t[sza(t)-2], t.back(), a[i], usecol))
					t.ppb();
				t.pb(a[i]);
			}
		}
	}
	
	if(usecol && sza(up) == sza(a)) {
		reverse(all(a));
		return a;
	}
	
	for(int i = sza(down) - 2; i > 0; i--) up.pb(down[i]);
	return up;
}