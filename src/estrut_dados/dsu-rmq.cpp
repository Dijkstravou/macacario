struct Query {
    int L, R, idx;
};

vector<int> answer;
// container[i] tem tds as queries com R=i
vector<vector<Query>> container;

// ...

stack<int> s;
for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] > a[i]) {
        parent[s.top()] = i;
        s.pop();
    }
    s.push(i);
    for (Query q : container[i]) {
        answer[q.idx] = a[find_set(q.L)];
    }
}