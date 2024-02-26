long long count_nonegative_solution(int a, int b, int c) {
    return find_all_solutions(ll(a), ll(b), ll(c), 0LL, ll(c / a + 1), 0LL, ll(c / b + 1));
}