int L = 0, R = -1, t = 0;

for (auto q : qs) {
    while (L > q.l)
        add(--L);
    while (R < q.r)
        add(++R);
    while (L < q.l)
        remove(L++);
    while (R > q.r)
        remove(R--);
    viajem_no_tempo(q.t, t, q.l, q.r);
    t = q.t;
    anses[q.id] = curr_ans;
}