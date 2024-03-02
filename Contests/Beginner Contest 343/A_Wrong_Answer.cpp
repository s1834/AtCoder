#include<bits/stdc++.h>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  
  int sum = a + b;
  if(sum == 0) {
    cout << 1 << endl;
  } else {
    cout << sum - 1 << endl;
  }
  return 0;
}