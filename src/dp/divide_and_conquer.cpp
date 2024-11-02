// N testado, mas copiei do cp algo
vi dp_before, dp_cur;

ll C(int i, int j);

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pii best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        smin(best, pii{(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }

    dp_cur[mid] = best.ff;
    int opt = best.ss;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

ll solve() {
    dp_before.assign(n,0);
    dp_cur.assign(n,0);

    F(n) dp_before[i] = C(0, i);

    F1(m-1) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }

    return dp_before[n - 1];
}