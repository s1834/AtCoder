#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long ans = 0;
    int j = 1;

    for (int i = 1; i <= n; i++) {
        if (j < i) j = i;

        while (j + 1 <= n) {
            cout << "? " << i << " " << j + 1 << endl;

            string pair;
            cin >> pair;

            if (pair == "Yes") j++;
            else break;
        }

        ans += j - i;
    }

    cout << "! " << ans << endl;

    return 0;
}