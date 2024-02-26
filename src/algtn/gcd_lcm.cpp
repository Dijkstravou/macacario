int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) { return a / gcd(a, b) * b; }

int iterative_gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Nao diminui complexidade mas acelera msm assim
// Nunca vi um problema que precisasse disso
int fast_gcd(int a, int b) {
    if (!a || !b) return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}