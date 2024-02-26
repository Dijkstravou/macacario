const int MAXN = 2e6 + 100;

std::vector<int> prime;
bool is_composite[MAXN];
int mu[MAXN];

void sieve(int n) {
    std::fill(is_composite, is_composite + n, false);
    mu[1] = 1;
    for (int i = 2; i < n; ++i) {
        if (!is_composite[i]) {
            prime.push_back(i);
            mu[i] = -1; // i is prime
        }
        for (int j = 0; j < prime.size() && i * prime[j] < n; ++j) {
            is_composite[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0; // prime[j] divides i
                break;
            } else {
                mu[i * prime[j]] = -mu[i]; // prime[j] does not divide i
            }
        }
    }
}