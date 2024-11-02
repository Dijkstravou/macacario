// N testado, mas copiei do cp algo

ll dp[maxn][maxn];
int opt[maxn][maxn];

ll C(int i, int j);

ll solve() {
    F(n) {
        opt[i][i] = i;
        dp[i][i] = 0 // depende do problema
    }

    for(int i = n-2; i >= 0; i--) {
        for(int j = i+1; j < n; j++) {
            ll mn = inf;
            ll cost = C(i, j);
            for(int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if(mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }

    return dp[0][n-1];
}