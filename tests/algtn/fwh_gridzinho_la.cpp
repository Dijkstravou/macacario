// https://csacademy.com/contest/archive/task/token-grid/

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const ll mod = 1e9 + 7;

ll fast_mod(ll k) {
    while (k >= mod)
        k -= mod;
    return k;
}

void FWT(vector<ll>& a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = fast_mod(x + y);
                // xor:a[i+j]=x+y,a[i+j+d]=x-y;
                // and:a[i+j]=x+y;
                // or:a[i+j+d]=x+y;
            }
}

void UFWT(vector<ll>& a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = fast_mod(x - y + mod);
                // xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                // and:a[i+j]=x-y;
                // or:a[i+j+d]=y-x;
            }
}

const int size_lim = 1 << 16;

vector<ll> mul_and(vector<vector<ll>>& vector_list) {
    vector<ll> la_respuesta(size_lim, 1);
    for (int i = 0; i < vector_list.size(); i++) {
        vector_list[i].resize(size_lim);
        FWT(vector_list[i], size_lim);
        for (int j = 0; j < size_lim; j++)
            la_respuesta[j] = (la_respuesta[j] * vector_list[i][j]) % mod;
    }
    UFWT(la_respuesta, size_lim);
    return la_respuesta;
}

int n, m;
vector<string> el_grid;

vector<vector<ll>> polys;

void add_col(int id_col) {
    vector<ll> other_poly((1 << n), 0);
    for (int i = 0; i < ((1 << n)); i++) {
        // essa mascara funciona? ela e a dos que
        // vou tirar. entao tenho que ver se os que fica
        // eles sao tudo igual
        char ultimo = 0;
        char nao_presta = 0;
        for (int j = 0; j < n; j++) {
            char atual = el_grid[j][id_col];
            if ((1 << j) & i) {
                continue;
            }
            // isso quer dizer que nao vou tirar o bit atual
            if (atual == '.') {
                // mas dai se for . eu na vdd tinha que ter tirado ne
                goto deuruim;
            }
            if (ultimo && ultimo != atual) {
                nao_presta = 1;
                break;
            }
            ultimo = atual;
        }
        if (!nao_presta) {
            other_poly[i] = 1; // ativo essa mascara
        }
    deuruim:
        i += 0;
    }
    /*cout << "my little poly\n";
    for (auto coeff : other_poly) {
        cout << coeff << " ";
    }
    cout << "\n";*/
    polys.push_back(other_poly);
}

int main() {
    cin >> n >> m;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        el_grid.push_back(s);
    }
    for (int i = 0; i < m; i++) {
        add_col(i);
    }
    vector<ll> el_prod = mul_and(polys);
    vector<ll> final_ans(n + 1, 0);
    for (int i = 0; i < (1 << n); i++) {
        int nbits = __builtin_popcount(i);
        final_ans[nbits] = fast_mod(final_ans[nbits] + el_prod[i]);
    }
    for (auto cara : final_ans) {
        cout << cara << " ";
    }
    cout << "\n";
}