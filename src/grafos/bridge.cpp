int tin[maxn], low[maxn];
int timer;
vector<pii> res;

void dfs(int v, int p=-1) {
    tin[v] = low[v] = ++timer;
    bool pskip = false;
    for(int u: g[v]) {
        if(u == p && !pskip) {
            pskip = true;
            continue;
        }
        if(tin[u] != 0) smin(low[v], tin[u]);
        else {
            dfs(u, v);
            smin(low[v], low[u]);
            if(low[u] > tin[v]) res.pb({v, u});
        }
    }
}

void find_bridges() {
    F1(n) if(tin[i] == 0) dfs(i);
}
