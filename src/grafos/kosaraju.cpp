bool vis[maxn];
int nc;
int root[maxn];

void dfs(int v, vi* g, vi &out) {
	vis[v] = true;
	for(auto u: g[v]) if(!vis[u]) dfs(u, g, out);
	out.pb(v);
}

void scc() {
	vi ord;
	memset(vis, false, sizeof(vis));
	F1(n) if(!vis[i]) dfs(i, g, ord);
	memset(vis, false, sizeof(vis));
	reverse(all(ord));
	for(auto v: ord) if(!vis[v]) {
		vi comp;
		dfs(v, gt, comp);
		int rt = ++nc;
		for(auto u: comp) root[u] = rt;
	}
}

