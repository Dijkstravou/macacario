const long long int mod = 1e9 + 7;
const long long int maxn = 1e9;
const int tempo = 1e6;
long long int fatmod[mod / tempo + 1] = {
    /* com outro programa calcular os numeros e copiar e colar aqui*/};

long long int computa_fatmod(int n) {
    if (n >= mod) return 0;
    long long int atual = fatmod[n / tempo];
    for (int i = (n / tempo) * tempo + 1; i <= n; i++) {
        atual *= i;
        atual %= mod;
    }
    return atual;
}
