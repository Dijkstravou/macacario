int g(int n) { return n ^ (n >> 1); }

void swap_peg(int& x) {
    if (x == 1)
        x = 2;
    else if (x == 2)
        x = 1;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1;; i++) {
        int gi = g(i - 1);
        int gip1 = g(i);
        int bitpos = gi ^ gip1;
        int pos_dude = __builtin_ctz(bitpos);
        if (pos_dude == n) break;
        int from_peg = (i & (i - 1)) % 3;
        int to_peg = ((i | (i - 1)) + 1) % 3;
        if (n % 2 == 0) {
            swap_peg(from_peg);
            swap_peg(to_peg);
        }
        cout << "Disco " << pos_dude << " vai de " << from_peg << " para " << to_peg << "\n";
    }
}