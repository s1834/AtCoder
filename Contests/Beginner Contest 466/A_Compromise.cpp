#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> v(n);
    bool flag = false;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        if(v[i] >= 0) flag = true;
    }
    
    if(flag) cout << "No\n";
    else cout << "Yes\n";
    
    return 0;
}