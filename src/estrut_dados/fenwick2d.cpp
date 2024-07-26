// temos um retangulo n x m e sum(x, y) retorna a soma em
// [1, x] cartesiano [1, y]
ll sum(int x, int y) {
    ll ret = 0;
    for (int i = x; i > 0; i -= i & (-i))
        for (int j = y; j > 0; j -= j & (-j))
            ret += bit[i][j];
    return ret;
}

// assumindo: x1 <= x2 e y1 <= y2
// soma do retangulo que vai de (x1, y1) ate (x2, y2)
ll sum_rect(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) + sum(x1 - 1, y1 - 1) - sum(x2, y1 - 1) - sum(x1 - 1, y2);
}

void add(int x, int y, ll delta) {
    for (int i = x; i <= n; i += i & (-i))
        for (int j = y; j <= m; j += j & (-j))
            bit[i][j] += delta;
}