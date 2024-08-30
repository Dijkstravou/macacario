// https://www.spoj.com/problems/QTREE/
// CHANGE i ti -- muda custo da aresta i pra ti
// QUERY a b -- custo maximo no caminho do no a ate o no b
// como o codigo do cp envolve vertices e nao arestas
// aqui eu disse que o custo de um vertice e o custo
// da aresta em cima dele
// entao na hora de fazer query eu nao considero
// o vertice de maior altura no caminho de a ate b

#include <bits/stdc++.h>

#define ESQ (2 * node)
#define DIR (2 * node + 1)
#define mid ((i + j) / 2)

using namespace std;

const int maxn = 1e4 + 100;
const int maxl = 15;

vector<vector<int>> adj;
vector<int> parent, depth, heavy, head, pos;
int cur_pos;
int anc[maxn][maxl];

int dfs(int v, vector<vector<int>> const& adj) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c, adj);
            size += c_size;
            if (c_size > max_c_size) max_c_size = c_size, heavy[v] = c;
        }
    }
    return size;
}

void decompose(int v, int h, vector<vector<int>> const& adj) {
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1) decompose(heavy[v], h, adj);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v]) decompose(c, c, adj);
    }
}

void init(vector<vector<int>> const& adj) {
    int n = adj.size();
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    cur_pos = 0;
    // cout << "aqui\n";
    dfs(0, adj);
    decompose(0, 0, adj);
    // cout << "nanii\n";
    // cout << n << "\n";
    // for (int i = 0; i < n; i++) {
    // cout << i << " -- pos[" << i << "] = " << pos[i] << "\n";
    //}
}

int seg[4 * maxn];
int arr[maxn];

void build(int node, int i, int j) {
    if (i == j) {
        seg[node] = arr[i];
        // cout << "build " << i << " -- " << j << " --- " << seg[node] << "\n";
        return;
    }
    build(ESQ, i, mid);
    build(DIR, mid + 1, j);
    seg[node] = max(seg[ESQ], seg[DIR]);
    // cout << "build " << i << " -- " << j << " --- " << seg[node] << "\n";
}

void upd(int node, int i, int j, int ind, int v) {
    if (ind < i || ind > j) return;
    if (i == j) seg[node] = v;
    if (i != j) {
        upd(ESQ, i, mid, ind, v);
        upd(DIR, mid + 1, j, ind, v);
        seg[node] = max(seg[ESQ], seg[DIR]);
    }
}

int qry(int node, int i, int j, int l, int r) {
    if (j < l || i > r) return INT32_MIN;
    if (l <= i && j <= r) return seg[node];
    return max(qry(ESQ, i, mid, l, r), qry(DIR, mid + 1, j, l, r));
}

int n;

int segment_tree_query(int l, int r) {
    // // cout << "aa " << l << " " << r << "\n";
    return qry(1, 0, n - 1, l, r);
}

int query_hld(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) swap(a, b);
        int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b]) swap(a, b);
    int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}

int pega_antes_l(int x, int l) {
    int antes_l = x;
    for (int ll = maxl - 1; ll >= 0; ll--) {
        if (anc[antes_l][ll] != -1 && depth[anc[antes_l][ll]] > depth[l])
            antes_l = anc[antes_l][ll];
    }
    return antes_l;
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) return lca(b, a);

    for (int l = maxl - 1; l >= 0; l--) {
        if (anc[a][l] != -1 && depth[anc[a][l]] >= depth[b]) {
            a = anc[a][l];
        }
    }
    // depth[a] = depth[b]
    if (a == b) return a;

    for (int l = maxl - 1; l >= 0; l--) {
        if (anc[a][l] != anc[b][l]) {
            a = anc[a][l];
            b = anc[b][l];
        }
    }
    return anc[a][0];
}

int query(int a, int b) {
    // a != b
    // // cout << "lca de " << a << " e " << b << " deu ";
    int l = lca(a, b);
    // // cout << l << "\n";
    if (l == a || l == b) {
        int outro = a == l ? b : a;
        return query_hld(outro, pega_antes_l(outro, l));
    }
    return max(query_hld(a, pega_antes_l(a, l)), query_hld(b, pega_antes_l(b, l)));
}

typedef tuple<int, int, int> ti;

void upd_tree(int v, int ti) { upd(1, 0, n - 1, pos[v], ti); }

void solve() {
    string s;
    // cout << "wtff\n";
    cin >> n;
    int a, b, c;
    vector<ti> edges;
    adj = vector<vector<int>>(n, vector<int>());
    // cout << "antes\n";
    for (int i = 0; i + 1 < n; i++) {
        cin >> a >> b >> c;
        a--;
        b--;
        edges.push_back({a, b, c});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // cout << "aquiii\n";
    init(adj);
    anc[0][0] = -1;
    for (int i = 1; i < n; i++) {
        anc[i][0] = parent[i];
    }
    for (int i = 1; i < maxl; i++) {
        for (int j = 0; j < n; j++) {
            anc[j][i] = anc[j][i - 1] == -1 ? -1 : anc[anc[j][i - 1]][i - 1];
        }
    }
    for (int i = 0; i + 1 < n; i++) {
        auto [a, b, c] = edges[i];
        if (parent[a] == b) swap(a, b);
        // a is the parent of b
        // cout << "Since " << a << " is the parent of " << b;
        // cout << " im setting arr[" << pos[b] << "] to " << c << "\n";
        arr[pos[b]] = c;
    }
    arr[0] = INT32_MIN;
    build(1, 0, n - 1);
    // cerr << "here\n";
    while (cin >> s) {
        if (s[0] == 'D') break;
        cin >> a >> b;
        if (s[0] == 'Q') {
            assert(a != b);
            a--;
            b--;
            cout << query(a, b) << "\n";
        } else {
            // a eh o numero da aresta
            // cerr << "a\n";
            auto [x1, x2, _] = edges[a - 1];
            // cerr << "aa\n";
            if (parent[x1] == x2) swap(x1, x2);
            // cerr << "aaa\n";
            upd_tree(x2, b);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
}