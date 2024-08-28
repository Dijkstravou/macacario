// recebe uma edge list das arestas entre os dois conjuntos de vertices do grafo bipartido, indexado no 0
// complexidade O(sqrt(V)E)
vector<pair<int, int> > hopcroft_karp(vector<pair<int, int> > e) {
    int n = -1, m = -1;
    shuffle(e.begin(), e.end(), mt19937(random_device{}()));
    for (auto &[u, v]: e)
        n = max(n, u + 1), m = max(m, v + 1);
    vector<int> deg(n + 1);
    for (auto &[u, v]: e) deg[u]++;
    partial_sum(deg.begin(), deg.end(), deg.begin());
    vector<int> g(e.size()), l(n, -1), r(m, -1), a, p, q(n);
    for (auto &[u, v]: e) g[--deg[u]] = v;
    while (true) {
        a.assign(n, -1), p.assign(n, -1);
        int t = 0;
        for (int i = 0; i < n; i++)
            if (l[i] == -1) q[t++] = a[i] = p[i] = i;
        bool match = false;
        for (int i = 0; i < t; i++) {
            int x = q[i];
            if (l[a[x]] != -1) continue;
            for (int j = deg[x]; j < deg[x + 1]; j++) {
                int y = g[j];
                if (r[y] == -1) {
                    while (y != -1)
                        r[y] = x, swap(l[x], y), x = p[x];
                    match = true;
                    break;
                }
                if (p[r[y]] == -1)
                    q[t++] = y = r[y], p[y] = x, a[y] = a[x];
            }
        }
        if (!match) break;
    }
    vector<pair<int, int> > ret;
    for (int i = 0; i < n; i++)
        if (l[i] != -1) ret.emplace_back(i, l[i]);
    return ret;
}
