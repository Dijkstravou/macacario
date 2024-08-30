// PODE INSERIR O MSM VERTICE > 1 VEZ
if(low[u] >= tin[v] && p != -1) res.pb(v);

// Fim da dfs
if(p == -1 && children > 1) res.pb(v);

// Sempre que o nó v chama dfs em um filho, ++children (local)
