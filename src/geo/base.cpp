typedef long long T;
struct pt {
	T x, y;
	pt(T x=0, T y=0): x(x), y(y) {} 
	pt operator+(pt o) { return pt(x+o.x, y+o.y); }
	pt operator-(pt o) { return pt(x-o.x, y-o.y); }
	//pt operator*(T a) { return pt(a*x, a*y); }
	T operator*(pt o) { return x*o.x + y*o.y; }
	T operator^(pt o) { return x*o.y - y * o.x; }
	//pt operator^(pt o) { return pt(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x); }
	T norm2() { return x*x + y*y; }
	ld norm() { return sqrt(norm2()); }
	bool operator<(pt o) const {
		if(x != o.x) return x < o.x;
		return y < o.y;
	}
};

// Testes insuficientes
ld ang(pt a, pt b) {
	return atan2(a^b, a*b);
}

// Determinante (vetores nas linhas). Volume paralelepípedo.
// Usar versao 3d do cross product (^)
// T triple(pt a, pt b, pt c) { return a * (b^c); }
