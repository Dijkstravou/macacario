// complexidade O(M), retorna vector dos vertices e das arestas onde cada elist[i] conecta vlist[i], vlist[i+1]
// elist são os indices das arestas (conforme a ordem de insercao, 0...M-1) do caminho euleriano 
// se vlist retornar vazio não existe caminho euleriano
struct edge {
	int t, id;
};

pair<vector<int>, vector<int>> eulerpath_undirected(int N, int M, const vector<pair<int, int>>& edges) {
	vector<vector<edge> > G(N);
	for (int i = 0; i < M; i++) {
		auto e = edges[i];
		G[e.first].push_back(edge{e.second, i});
		G[e.second].push_back(edge{e.first, i});
	}
	int start = -1, cnt = 0;
	for (int i = 0; i < N; i++) {
		if (G[i].size() % 2 == 1) {
			start = i;
			cnt++;
		}
	}
	if (cnt >= 4) return {vector<int>(), vector<int>()};
	if (cnt == 0) start = (M != 0 ? edges[0].s : 0);
	vector<bool> used(M, false);
	vector<int> vlist, elist;
	auto dfs = [&](auto& self, int v) -> void {
		while (!G[v].empty()) {
			edge e = G[v].back();
			G[v].pop_back();
			if (!used[e.id]) {
				used[e.id] = true;
				self(self, e.t);
				elist.push_back(e.id);
			}
		}
		vlist.push_back(v);
	};
	dfs(dfs, start);
	reverse(vlist.begin(), vlist.end());
	reverse(elist.begin(), elist.end());
	if (elist.size() != M) return {vector<int>(), vector<int>()};
    
	return {vlist, elist};
}
