#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; 
    cin >> n;
    
    int a, b;
    string s;
    int keep = 0;
    for(int i = 0; i < n; i++){
        cin >> a >> b >> s;
        if(s == "keep") keep += b - a;
    } 
    
    cout << keep << endl;
    return 0;
}

/*

Idea:
------
The only money Takahashi loses is the change that he
chooses not to receive.

For each purchase,

Change = Amount Paid - Item Cost

= B - A

If

S == "keep"

he does not receive this change, so it contributes to
the total loss.

If

S == "take"

he receives the change, so there is no loss.

Therefore, the required answer is simply the sum of
(B - A) for every store where the change is kept.

------------------------------------------------------------

Algorithm:
----------

1.

Read N.

2.

For each store,

read

A, B, and S.

3.

If

S == "keep"

add

(B - A)

to the total loss.

4.

After processing all stores,

print the total loss.

------------------------------------------------------------

Why This Works:
---------------

Suppose

Initial Money = 10000

If Takahashi always receives the change,

his money decreases only by the item's cost A.

If he keeps the change,

his money decreases by the amount paid B.

Hence,

Loss at one store

= B - A

Since each store is independent,

the total loss is simply the sum of these losses over
all stores where

S == "keep".

------------------------------------------------------------

Example:
--------

Input

3

1 2 keep

3 6 take

5 9 keep

Store 1

Loss = 2 - 1 = 1

Store 2

Received change.

Loss = 0

Store 3

Loss = 9 - 5 = 4

Total Loss

1 + 4 = 5

Output

5

------------------------------------------------------------

Time Complexity:
----------------

O(N)

Each store is processed exactly once.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few variables are used.

*/