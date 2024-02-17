//https://cses.fi/problemset/task/1145
#include <bits/stdc++.h>
using namespace std;

typedef long long li;

#define MAXN 200010

const li INF = 1e10;

li a[MAXN], dp[MAXN];
li n;

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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	cout << lis() << endl;
}