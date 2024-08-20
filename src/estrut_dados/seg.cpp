// 1 indexado

#define EL 2*i, l, (l+r)/2 
#define ER 2*i+1, (l+r)/2+1, r
#define INI 1, 1, n

struct Node {
    ll v;

    Node(ll v=0): v(v) {}
    Node operator+(Node ot) { return Node(v+ot.v); }
    void update(ll _v) {v = _v;}
};

struct Seg {
    Node dt[4*maxn];

    Node build(int i, int l, int r) {
        if(l == r) return dt[i] = Node(a[r]);
        return dt[i] = build(EL) + build(ER);
    }

    Node query(int ql, int qr, int i, int l, int r) {
        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return dt[i];
        return query(ql, qr, EL) + query(ql, qr, ER);
    }

    Node update(int pos, ll v, int i, int l, int r) {
        if(r < pos || l > pos) return dt[i];
        if(l == r) {
            dt[i].update(v);
            return dt[i];
        }

        return dt[i] = update(pos, v, EL) + update(pos, v, ER);
    }
};