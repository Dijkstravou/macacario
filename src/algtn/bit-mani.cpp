bool isPowerOfTwo(unsigned int n) { return n && !(n & (n - 1)); }

int countSetBits(int n) {
    int count = 0;
    while (n) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

// n & (n+1) limpa os trailing ones
// n | (n+1) seta o último bit zero
// n & (-n) extrai o último bit

// __builtin_popcount(unsigned int) numero de bits um

// __builtin_ffs(int) índice do bit 1 mais a direita

// __builtin_clz(unsigned int) -> qnt de leading zeros

// __builtin_ctz(unsigned int) -> qnt de trailing zeros

// __builtin_parity() -> paridade do número de uns

// NOTA: algumas dessas podem ser lentas no GCC se nao ativar um target específico de compilador com
// #pragma GCC target("popcnt")
