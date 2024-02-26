const int B = 12; // nesse problema os pols envolvidos tinham no max x^800 y^800
const int N = 1 << B;

cd roots[N];
int inv[N];

cd get_root(int k, int n) { return roots[k * (N / n)]; }

void precalc() {
    for (int i = 0; i < N; i++) {
        double ang = 2 * PI * i / N;
        roots[i] = cd(cos(ang), sin(ang));
    }
}

bool bit(int mask, int i) { return (mask >> i) & 1; }

void precalc_inv(int n) {
    int b = 0;
    while ((1 << b) < n)
        ++b;
    assert((1 << b) == n);
    assert(b <= B);

    inv[0] = 0;
    int hb = -1;
    for (int i = 1; i < n; ++i) {
        if (bit(i, hb + 1)) {
            ++hb;
        }
        inv[i] = inv[i ^ (1 << hb)] ^ (1 << (b - hb - 1));
    }
}

// ****copia e cola fft aq

void fft_2d(vector<vector<cd>>& a, bool rev) {
    precalc_inv((a[0].size()));
    for (auto& row : a) {
        fft(row, rev);
    }
    precalc_inv((a.size()));
    for (int j = 0; j < a.front().size(); j++) {
        vector<cd> col;
        for (int i = 0; i < a.size(); i++)
            col.push_back(a[i][j]);
        fft(col, rev);
        for (int i = 0; i < a.size(); i++)
            a[i][j] = col[i];
    }
}

vector<vector<cd>> mult(vector<vector<cd>> x, vector<vector<cd>> y) {
    int b_rows = 0;
    while ((1 << b_rows) <= max(x.size(), y.size()))
        ++b_rows;
    ++b_rows;

    int b_cols = 0;
    while ((1 << b_cols) <= max(x.front().size(), y.front().size()))
        ++b_cols;
    ++b_cols;

    x.resize(1 << b_rows);
    y.resize(1 << b_rows);
    for (auto& row : x) {
        row.resize(1 << b_cols, 0);
    }
    for (auto& row : y) {
        row.resize(1 << b_cols, 0);
    }

    fft_2d(x, 0);
    fft_2d(y, 0);

    for (int i = 0; i < x.size(); i++)
        for (int j = 0; j < x[i].size(); j++)
            x[i][j] *= y[i][j];

    fft_2d(x, 1);

    return x;
}
