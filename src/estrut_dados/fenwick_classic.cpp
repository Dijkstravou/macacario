// voce tem um array[1..n] de input. faz um vetor bit de maxn zerado
// pra inicializar, faz update(i, arr[i]) pra cada i
// (isso adiciona arr[i] no indice i em log)
// o resto e obvio
ll sum(int idx) { // soma ate idx
    ll ret = 0;
    for (; idx > 0; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}

ll sum_interval(int l, int r) { return sum(r) - sum(l - 1); }

void add(int idx, ll delta) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += delta;
}