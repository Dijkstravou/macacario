//https://cses.fi/problemset/task/1158

#include <bits/stdc++.h>

using namespace std;

#define MAXCAP 100010
#define MAXN 1001

typedef long long li;

li v[MAXN], p[MAXN], dp[MAXCAP];
li n, C;

li ks() {
	for(int i = 0; i < n; i++)
		for(li c = C; c>=p[i]; c--) 
			dp[c] = max(dp[c], dp[c-p[i]] + v[i]);
	return dp[C];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> C;
	for(int i = 0; i < n; i++)
		cin >> p[i];
	for(int i = 0; i < n; i++)
		cin >> v[i];
		
	cout << ks() << endl;
}
