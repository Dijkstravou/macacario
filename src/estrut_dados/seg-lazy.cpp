// 1 indexado

#define LEFT 2*i 
#define RIGHT 2*i+1

#define EL LEFT, l, (l+r)/2 
#define ER RIGHT, (l+r)/2+1, r
#define INI 1, 1, n

struct Node {
    ll v, acc=0;  // Adiciona acumulador 

    Node(ll v=0): v(v) {}
    Node operator+(Node ot) { return Node(v+ot.v); }

    // Update apenas marca 
    void update(ll _v) {acc = _v;}
    // Realmente aplica update. CUIDADO SE NAO VERIFICOU SE TA MARCADO
    void apply(int l, int r) { v = acc * (r-l+1); }
};

struct Seg {
    Node dt[4*maxn];
    bool mark[4*maxn]; // Se tem update

    Node build(int i, int l, int r) {
        mark[i] = false; // Inicializa mark
        if(l == r) return dt[i] = Node(a[r]);
        return dt[i] = build(EL) + build(ER);
    }

    void flush(int i, int l, int r) {
        if(l != r) {
            dt[LEFT].update(dt[i].acc);
            dt[RIGHT].update(dt[i].acc);
            mark[LEFT] = mark[RIGHT] = true;
        }
        dt[i].apply(l, r);
        mark[i] = false;
    }

    Node query(int ql, int qr, int i, int l, int r) {
        if(mark[i]) flush(i, l, r);

        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return dt[i];
        return query(ql, qr, EL) + query(ql, qr, ER);
    }

    Node update(int ql, int qr, ll v, int i, int l, int r) {
        if(mark[i]) flush(i, l, r);

        if(l > qr || r < ql) return dt[i];
        if(ql <= l && r <= qr) {
            dt[i].update(v);
            flush(i, l, r);
            return dt[i];
        }

        return dt[i] = update(ql, qr, v, EL) + update(ql, qr, v, ER);
    }
};