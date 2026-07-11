#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> queryRow(m + 1), queryColumn(m + 1);
    vector<int> lastRow(n + 1, 0), lastColumn(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        cin >> queryRow[i] >> queryColumn[i];
        lastRow[queryRow[i]] = i;
        lastColumn[queryColumn[i]] = i;
    }

    int ans = 0;

    for (int i = 1; i <= m; i++) {
        if (lastRow[queryRow[i]] == i && lastColumn[queryColumn[i]] == i)
            ans++;
    }

    cout << ans << endl;
    return 0;
}