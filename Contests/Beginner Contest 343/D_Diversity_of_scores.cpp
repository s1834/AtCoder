#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    
    vector<int> ans;
    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        mp[i] = 0;
    }
    int a, b;
    for (int i = 0; i < t; i++) {
      cin >> a >> b;
      mp[a] += b;
      
      set<int> s;
      for(auto i : mp) {
        s.insert(i.second);
      }
      ans.push_back(s.size());
    }
    
    for (int i = 0; i < ans.size(); i++) {
      cout << ans[i] << endl;
    }

    return 0;
}
