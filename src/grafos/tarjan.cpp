int tin[maxn], low[maxn];
int timer;
int nc;
int root[maxn];

void dfs(int v, vi &st) {
    tin[v] = low[v] = ++timer;
	st.pb(v);
	
    for(int u: g[v]) {
        if(tin[u] == 0) dfs(u, st);
		if(root[u] == 0) smin(low[v], low[u]);
    }

	if(low[v] == tin[v]) {
		int lst;
		++nc;		
		do {
			lst = st.back();
			st.ppb();
			root[lst] = nc;
		} while(lst != v);
	}
}

F1(n) if(tin[i] == 0) {
	vi st;
	dfs(i, st);
}

