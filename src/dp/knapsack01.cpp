// li v[MAXN], p[MAXN], dp[MAXCAP];
// li n, C;
// 0 indexado

li ks() {
	for(int i = 0; i < n; i++) 
		for(li c = C; c >= p[i]; c--) 
			dp[c] = max(dp[c], dp[c-p[i]] + v[i]);
	return dp[C];
}
