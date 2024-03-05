// 1 indexado
ll a[maxn], dp[maxn];
ll n;

int lis() {
	for(int i = 1; i <= n; i++) dp[i] = inf;
	for(int i = 1; i <= n; i++) {
		int x = lower_bound(dp+1, dp+1+n, a[i]) - dp-1;
		dp[x+1] = min(dp[x+1], a[i]);
	}
	
	for(int i = n; i > 0; i--) 
		if(dp[i] != inf) return i;
	return 0;
}
