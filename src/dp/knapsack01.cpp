// 0 indexado
ll v[maxn], p[maxn], dp[MAXCAP];
ll n, C;

ll ks() {
	for(int i = 0; i < n; i++) 
		for(li c = C; c >= p[i]; c--) 
			dp[c] = max(dp[c], dp[c-p[i]] + v[i]);
	return dp[C];
}
