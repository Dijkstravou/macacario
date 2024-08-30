#include <bits/stdc++.h>

#define MAX 30000
#define MVAL 1000100
#define MRESPS 200100

using namespace std;

int n, q;
int arr[MAX];
int freqs[MVAL];
int respostas[MRESPS];
int ans = 0;
int bl;

struct Query {
    int l, r, id;
    bool operator<(Query other) const {
        return make_pair(l / bl, r) < make_pair(other.l / bl, other.r);
    }
};

void add(int x) {
    x = arr[x];
    freqs[x]++;
    if (freqs[x] == 1) {
        ans++;
    }
}

void remove(int x) {
    x = arr[x];
    freqs[x]--;
    if (freqs[x] == 0) {
        ans--;
    }
}

int main() {

    memset(freqs, 0, sizeof(freqs));

    cin >> n;
    bl = sqrt(n + 0.0) + 1;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cin >> q;
    int l, r;
    vector<Query> queries;

    for (int i = 0; i < q; i++) {
        Query qq;
        cin >> qq.l >> qq.r;
        qq.l--;
        qq.r--;
        qq.id = i;
        queries.push_back(qq);
    }

    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;

    for (int i = 0; i < q; i++) {
        while (cur_l > queries[i].l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < queries[i].r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < queries[i].l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > queries[i].r) {
            remove(cur_r);
            cur_r--;
        }
        respostas[queries[i].id] = ans;
    }

    for (int i = 0; i < q; i++) {
        cout << respostas[i] << "\n";
    }

    return 0;
}
