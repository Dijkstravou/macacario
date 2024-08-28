// 1 indexado

#define EL 2*i, l, (l+r)/2 
#define ER 2*i+1, (l+r)/2+1, r
#define INI 1, 1, n
#define INIY 1, 1, m

struct Node {
    ll v;

    Node(ll v=0): v(v) {}
    Node operator+(Node ot) { return Node(v+ot.v); }
    void update(ll _v) {v = _v;}
};

struct Seg {
    Node dt[4*maxn][4*maxm];

	// Build nao testado
	void buildy(int xi, int xl, int xr, int i, int l, int r) {
		if(l == r) {
			if(xl == xr) dt[xi][i] = a[xr][r];
			else dt[xi][i] = dt[xi*2][i] + dt[xi*2+1][i];
		} else {
			buildy(xi, xl, xr, EL); buildy(xi, xl, xr, ER);
			dt[xi][i] = dt[xi][i*2] + dt[xi][i*2+1];
		}
	}
	
	void buildx(int i, int l, int r) {
		if(l != r) { buildx(EL); buildx(ER); }
		buildy(i, l, r, INIY);
	}
	
	Node query_y(int ql, int qr, int xi, int i, int l, int r) {
		if(l > qr || r < ql) return Node();
		if(ql <= l && r <= qr) return dt[xi][i];
		return query_y(ql, qr, xi, EL) + query_y(ql, qr, xi, ER);
	}

	Node query_x(int ql, int qr, int qyl, int qyr, int i, int l, int r) {
		if(l > qr || r < ql) return Node();
		if(ql <= l && r <= qr) return query_y(qyl, qyr, i, INIY);
		return query_x(ql, qr, qyl, qyr, EL) + query_x(ql, qr, qyl, qyr, ER);
	}

	Node update_y(int qy, int novo, int xi, int xl, int xr, int i, int l, int r) {
		if(r < qy || l > qy) return dt[xi][i];
		if(l == r) {
			if(xl == xr) dt[xi][i].update(novo);
			else dt[xi][i] = dt[xi*2][i] + dt[xi*2+1][i];
			return dt[xi][i];
		}
		return dt[xi][i] = update_y(qy, novo, xi, xl, xr, EL) + update_y(qy, novo, xi, xl, xr, ER);
	}

	void update_x(int qx, int qy, int novo, int i, int l, int r) {
		if(r < qx || l > qx) return;
		if(l != r) {
			update_x(qx, qy, novo, EL); update_x(qx, qy, novo, ER);
		}
		update_y(qy, novo, i, l, r, INIY);
	}
};
