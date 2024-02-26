vector<int> pi = prefix_function(s + "#" + t);
int n = s.size();
int m = t.size();
vector<int> ans(n + m + 1);
for (int i = n + 1; i < n + m + 1; i++)
    ans[pi[i]]++;
for (int i = n; i > 0; i--)
    ans[pi[i - 1]] += ans[i];
// Nossa resposta eh ans[i+1]