// 1 indexado
// Note que EL, ER mudaram um pouco

#define EL l, (l + r) / 2
#define ER (l + r) / 2 + 1, r
#define INI 1, n

struct Node {
    ll v;
    Node *l, *r;

    Node(ll v = 0) : v(v), l(0), r(0) {}
    Node(Node* l, Node* r) : l(l), r(r), v(0) {
        // Merge de nos eh aqui
        if (l) v += l->v;
        if (r) v += r->v;
    }
};

Node* roots[maxop];

Node* build(int l, int r) {
    if (l == r) return new Node(a[r]);
    return new Node(build(EL), build(ER));
}

// Atencao que aqui não retorna ponteiro
Node query(int ql, int qr, Node* v, int l, int r) {
    if (l > qr || r < ql) return Node();
    if (ql <= l && r <= qr) return *v;
    Node q1 = query(ql, qr, v->l, EL), q2 = query(ql, qr, v->r, ER);
    return Node(&q1, &q2);
}

Node* update(int pos, ll upd, Node* v, int l, int r) {
    if (r < pos || l > pos) return v;
    if (l == r) {
        return new Node(v->v + upd);
    }

    return new Node(update(pos, upd, v->l, EL), update(pos, upd, v->r, ER));
}