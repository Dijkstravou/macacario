typedef long long int T;
struct pt {
	T x, y;
	pt(T x, T y): x(x), y(y) {} 
	pt operator+(pt ot) { return pt(x+ot.x, y+ot.y); }
	pt operator-(pt ot) { return pt(x-ot.x, y-ot.y); }
	//pt operator*(T a) { return pt(a*x, a*y); }
	T operator*(pt ot) { return x*ot.x + y*ot.y; }
	T operator^(pt ot) { return x*ot.y - y * ot.x; }
	//pt operator^(pt ot) { return pt(y*ot.z - z*ot.y, z*ot.x - x*ot.z, x*ot.y - y*ot.x); }
	T norm2() { return x*x + y*y; }
	// double norm() { return sqrt(norm2()); }
	bool operator<(pt ot) const {
		if(x != ot.x) return x < ot.x;
		return y < ot.y;
	}
};
