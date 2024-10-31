// Lembra de declarar o n dentro da seg
// Aqui ta como point update
// LEMBRA DE CHAMAR O BUILD  DA HLD

// Intervalo da seg eh [0, n)
#define INI 1, 0, n-1

struct Hld {
    int n, head;
    vi verts;
    Seg s;
 
    void build() {
        n = sza(verts);
        head = *verts.rbegin();

        // Inicializa valores da seg aqui
        vi sa(n);
        F(n) sa[i] = a[verts[i]];
        s = Seg(n);
        s.build(sa, INI);
    }
 
    ll query(int ql, int qr) { return s.query(ql, qr, INI); }
    ll query_end(int ql) { return s.query(ql, n-1, INI); }
    void update(int pos, ll v) { s.update(pos, v, INI); }
};

pii hldid[maxn];
int sztree[maxn], anc[maxn];
vector<Hld> hld;
 
void dfshld(int v, int p=0) {
    anc[v] = p;
    sztree[v] = 1;
 
    for(auto u: g[v]) if(u != p) {
        dfshld(u, v);
        sztree[v] += sztree[u];
    }
 
    int heavy = -1;
    for(auto u: g[v]) if(u != p) {
        if(2*sztree[u] >= sztree[v])
            heavy = u;
    }
 
    if(heavy == -1) {
        hldid[v] = {sza(hld), 0};
        hld.pb(Hld());
    } else {
        hldid[v] = hldid[heavy];
        hldid[v].ss++;
    }
 
    hld[hldid[v].ff].verts.pb(v);
}
 
void hld_update(int v, ll qtd) {
    auto [hid, hpos] = hldid[v];
    hld[hid].update(hpos, qtd);
}
 
// Inclusivo
ll hld_query(int v, int fim) { 
    auto [hid, hpos] = hldid[v];
    auto [hidfim, hposfim] = hldid[fim];
 
    if(hid == hidfim) return hld[hid].query(hpos, hposfim);
    ll res = hld[hid].query_end(hpos);
 
    // Lembra de mudar aqui tambem, dependendo de como une 
    int prox = anc[hld[hid].head];
    if(prox) res += hld_query(prox, fim);
    return res;
}

// NA MAIN
dfshld(1);
for(auto &h: hld) h.build();
