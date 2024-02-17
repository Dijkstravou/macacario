// li a[MAXN], dp[MAXN];
// li n;
// 1 indexado

int lis() {
	for(int i = 1; i <= n; i++) dp[i] = INF;
	for(int i = 1; i <= n; i++) {
		int x = lower_bound(dp+1, dp+1+n, a[i]) - dp-1;
		dp[x+1] = min(dp[x+1], a[i]);
	}
	
	for(int i = n; i > 0; i--) 
		if(dp[i] != INF) return i;
	return 0;
}
