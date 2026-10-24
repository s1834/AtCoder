#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    
    int sum = a + b;
    int count = 0;
    while(sum) {
        sum /= 10;
        count++;
    }
    
    cout << count << endl;
    
    return 0;
}