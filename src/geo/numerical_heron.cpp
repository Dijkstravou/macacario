ld heron2(ld a, ld b, ld c) {
    // Sort a, b, c into descending order
    if (a < b) swap(a, b);
    if (a < c) swap(a, c);
    if (b < c) swap(b, c);
    ld p = (a + (b + c)) * (c - (a - b)) * (c + (a - b)) * (a + (b - c));
    return 0.25 * sqrtl(p);
}