const ll rev = inverse(2);

void FWT(vector<ll>& a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) % mod, a[i + j + d] = (x - y + mod) % mod;
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
                a[i + j] = 1LL * (x + y) * rev % mod,
                      a[i + j + d] = (1LL * (x - y) * rev % mod + mod) % mod;
                // xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                // and:a[i+j]=x-y;
                // or:a[i+j+d]=y-x;
            }
}

// tambem da pra usar pra or (eu acho :3)
vector<ll> mul_xor(const vector<ll>& v1, const vector<ll>& v2) {
    vector<ll> p1(v1.begin(), v1.end());
    vector<ll> p2(v2.begin(), v2.end());
    vector<ll> res;
    int novosize = 1;
    while (p1.size() + p2.size() > novosize) {
        novosize <<= 1;
    }
    p1.resize(novosize);
    p2.resize(novosize);
    res.resize(novosize);
    FWT(p1, novosize);
    FWT(p2, novosize);
    for (int i = 0; i < novosize; i++)
        res[i] = (p1[i] * p2[i]) % mod;
    UFWT(res, novosize);
    if (novosize > size_lim) res.resize(size_lim);
    return res;
}

// size_lim = 1<<16 no problema que resolvi
// isso aqui multiplica uma lista de vetores
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