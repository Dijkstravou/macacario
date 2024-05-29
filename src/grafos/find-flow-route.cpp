// lembrando que isso passou do Distinct Routes do CSES
// dentro do struct
void build_from_edges() {
    for (Edge e : in_sequence) {
        int from = adj[e.to][e.rev].to;
        if (e.flow() == 0 || e.oc == 0) continue;
        from_edges[from].push_back(e.to);
    }
}

// fora do struct
void the_dfs(int v) {
    path.push_back(v);
    if (d.from_edges[v].size()) {
        the_dfs(d.from_edges[v].back());
        d.from_edges[v].pop_back();
    }
}

// na main
cout << d.calc(0, n - 1) << "\n";
d.build_from_edges();
for (auto v : d.from_edges[0]) {
    path.clear();
    path.push_back(0);
    the_dfs(v);
    cout << path.size() << "\n";
    for (auto cara : path) {
        cout << cara + 1 << " ";
    }
    cout << "\n";
}