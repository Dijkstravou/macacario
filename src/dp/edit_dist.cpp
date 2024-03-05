string s, t;
int dp[maxn][2];

int ed_dist() {
	int c = 1;
	for(int i = 1; i <= sza(t); i++) dp[i][0] = i;
	
	for(int i = 1; i <= sza(s); i++, c^=1) {
		dp[0][c] = i;
		for(int j = 1; j <= sza(t); j++) {
			dp[j][c] = dp[j-1][c^1] + (s[i-1] != t[j-1]);
			dp[j][c] = min(dp[j][c], 1+min(dp[j][c^1], dp[j-1][c]));
		}
	}
	
	return dp[t.size()][c^1];
}
