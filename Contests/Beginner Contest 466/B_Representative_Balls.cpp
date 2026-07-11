#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> c(n), s(n), ans(m, -1);
    for(int i = 0; i < n; i++) {
        cin >> c[i] >> s[i];
        if(ans[c[i] - 1] < s[i]) ans[c[i] - 1] = s[i];
    }
    
    for(auto x : ans) cout << x << " ";
    
    return 0;
}