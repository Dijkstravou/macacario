// NAO E exatamente esse problema
// recebo duas fitas de DNA |s| >= |r|
// determinar r.size() - maior produto interno
// ou seja eu vou deslizando r em s (sem passar dos limites)
#include <bits/stdc++.h>

using namespace std;

using cd = complex<double>;
const double PI = acos(-1);
typedef long long int lli;

void fft(vector<cd>& a, bool invert) {}

vector<lli> multiply(vector<lli> const& a, vector<lli> const& b) {}

int conversion_map[200];

int main() {
    string s;
    string r;
    cin >> s;
    cin >> r;
    conversion_map['A'] = 0;
    conversion_map['C'] = 1;
    conversion_map['T'] = 2;
    conversion_map['G'] = 3;

    vector<lli> pols_s[4];
    vector<lli> pols_r[4];
    vector<lli> prods[4];
    for (int i = 0; i < s.size(); i++) {
        int atual = conversion_map[s[i]];
        for (int j = 0; j < 4; j++) {
            pols_s[j].push_back(atual == j);
        }
    }

    for (int i = 0; i < r.size(); i++) {
        int atual = conversion_map[r[i]];
        for (int j = 0; j < 4; j++) {
            pols_r[j].push_back(atual == j);
        }
    }

    for (int j = 0; j < 4; j++) {
        reverse(pols_r[j].begin(), pols_r[j].end());
        prods[j] = multiply(pols_s[j], pols_r[j]);
        if (prods[j].size() < s.size() - 1) prods[j].resize(s.size() - 1);
    }

    int max_ans = -1;

    for (int i = r.size() - 1; i <= s.size() - 1; i++) {
        int curr_ans = 0;
        for (int j = 0; j < 4; j++) {
            curr_ans += prods[j][i];
        }
        if (curr_ans > max_ans) {
            max_ans = curr_ans;
        } else if (curr_ans < max_ans)
            continue;
    }

    cout << r.size() - max_ans << "\n";
}
