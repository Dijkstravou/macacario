void dsumerge(int x, int y) {
    x = find(x);
    y = find(y);
    parents[x] = parents[y] = max(x, y);
}

// no for de dentro do int v = find_set(l), coloca
// dsumerge(v, v+1) ao inves de parent[v] = v+1
// otimizacao de 1.32s pra 1.12s no SPOJ/CFLARR