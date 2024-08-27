// 1 indexado
// Note que EL, ER mudaram um pouco

#define EL l, (l + r) / 2
#define ER (l + r) / 2 + 1, r
#define INI &seg.root, 1, n

struct Node {
    ll v;
    Node *l, *r;

    Node(ll v = 0) : v(v), l(0), r(0) {}
	void merge(Node l, Node r) {
		v = l.v + r.v;
	}
	void merge() { merge(*l, *r); }
	void update(ll _v) { v = _v; }
};

struct Seg {
	Node root;

	// Cuidado se for fazer lazy, tem que verificar se nao eh folha antes
	inline void extend(Node *v) {
		if(v->l == 0) {
			v->l = new Node();
			v->r = new Node();
		}
	}

	void update(ll pos, ll x, Node *v, ll l, ll r) {
		if(r < pos || l > pos) return;
		if(l == r) {
			v->update(x);
			return;
		}
		
		extend(v);
		update(pos, x, v->l, EL); update(pos, x, v->r, ER);
		v->merge();
	}

    Node query(int ql, int qr, Node *v, int l, int r) {
        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return *v;

		extend(v);
		
		Node res;
		res.merge(query(ql, qr, v->l, EL), query(ql, qr, v->r, ER));
        return res;
    }
};

