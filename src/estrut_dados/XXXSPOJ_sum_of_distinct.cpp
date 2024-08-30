#include <bits/stdc++.h>

const int maxn = 5e4 + 100;
const int maxq = 1e6 + 100;
const int B = 1700;

using namespace std;

int n, m;
int arr[maxn], cp_arr[maxn], freqs[maxn + maxq];
long long int anses[maxq];
int is_query[maxq];

unordered_map<int, int> ids;
int idsa[maxn];

long long int curr_ans = 0;

struct Q {
    int l, r, id, t, ce;
    Q(int l, int r, int id, int t) : l(l), r(r), id(id), t(t) {}
    bool operator<(const Q& q2) const {
        if (l / B > q2.l / B) return false;
        if (l / B < q2.l / B) return true;
        if (r / B > q2.r / B) return false;
        if (r / B < q2.r / B) return true;
        return t < q2.t;
    }
};

vector<Q> qs;
vector<Q> ups;

void viagem_no_tempo(int t_novo, int t_antes, int l, int r) {
    int i;
    int idupsir, idupsil, idupsirid;
    for (i = t_antes; i <= t_novo - 1; i++) {

        if (l <= ups[i].l && ups[i].l <= r) {
            idupsir = ups[i].t;
            idupsil = idsa[ups[i].l];
            freqs[idupsir]++;
            if (freqs[idupsir] == 1) curr_ans += ups[i].r;
            freqs[idupsil]--;
            if (freqs[idupsil] == 0) curr_ans -= arr[ups[i].l];
        }
        arr[ups[i].l] = ups[i].r;
        idsa[ups[i].l] = ups[i].t;
    }
    for (i = t_antes - 1; i > t_novo - 1; i--) {

        idupsirid = ups[i].ce;
        idupsil = idsa[ups[i].l];
        // Quero remover a update i
        if (l <= ups[i].l && ups[i].l <= r) {
            freqs[idupsirid]++;
            if (freqs[idupsirid] == 1) curr_ans += ups[i].id;
            freqs[idupsil]--;
            if (freqs[idupsil] == 0) curr_ans -= arr[ups[i].l];
        }
        arr[ups[i].l] = ups[i].id; // id da update = valor antes dela
        idsa[ups[i].l] = ups[i].ce;
    }
}

void add(int x) {
    freqs[idsa[x]]++;
    if (freqs[idsa[x]] == 1) curr_ans += arr[x];
}

void remove(int x) {
    freqs[idsa[x]]--;
    if (freqs[idsa[x]] == 0) curr_ans -= arr[x];
}

int main() {

    memset(freqs, 0, sizeof(freqs));

    cin >> n;
    int curr_id = 0;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        cp_arr[i] = arr[i];
        if (ids.find(arr[i]) == ids.end()) ids[arr[i]] = curr_id++;
    }

    cin >> m;

    char op;
    int tempo = 0;
    int l, r;

    for (int i = 0; i < m; i++) {
        cin >> op >> l >> r;
        anses[i] = 0;
        if (op == 'Q') {
            is_query[i] = 1;
            l--;
            r--;
            qs.push_back(Q(l, r, i, tempo));
        } else if (op == 'U') {
            is_query[i] = 0;
            l--;
            ups.push_back(Q(l, r, cp_arr[l], ++tempo));
            if (ids.find(r) == ids.end()) ids[r] = curr_id++;
            ups[(int)ups.size() - 1].t = ids[r];
            ups[(int)ups.size() - 1].ce = ids[cp_arr[l]];
            cp_arr[l] = r;
        }
    }

    for (int i = 0; i < n; i++)
        idsa[i] = ids[arr[i]];

    sort(qs.begin(), qs.end());

    int L = 0, R = -1, t = 0;

    for (auto q : qs) {
        while (L > q.l)
            add(--L);
        while (R < q.r)
            add(++R);
        while (L < q.l)
            remove(L++);
        while (R > q.r)
            remove(R--);
        viagem_no_tempo(q.t, t, q.l, q.r);
        t = q.t;
        anses[q.id] = curr_ans;
    }

    for (int i = 0; i < m; i++)
        if (is_query[i]) cout << anses[i] << "\n";
}