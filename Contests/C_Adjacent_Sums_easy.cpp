#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(n - 1);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) cin >> b[i];

    int ans = INT_MAX;
    for (int i = 0; i <= 1; i++) {
        int ops = 0;
        int curr = i;

        if (curr != a[0]) ops++;

        for (int j = 0; j < n - 1; j++) {
            int nxt = curr ^ b[j];

            if (nxt != a[j + 1]) ops++;

            curr = nxt;
        }

        ans = min(ans, ops);
    }

    cout << ans << endl;

    return 0;
}

/*

Idea:
------
Since M = 2, every element can only have two possible
remainders:

0 or 1.

Only the parity (even/odd) of each element matters.

Adding 1 to an element flips its parity.

If an element's current parity differs from the required
parity, exactly one operation is needed to fix it.

------------------------------------------------------------

Key Observation:
----------------

The condition is

(A[i] + A[i+1]) % 2 = B[i]

Let

P[i] = parity of A[i]

Then,

P[i] XOR P[i+1] = B[i]

because for modulo 2,

addition modulo 2 is equivalent to XOR.

Therefore,

once the parity of the first element is fixed,

the parity of every remaining element is uniquely
determined.

------------------------------------------------------------

Algorithm:
----------

There are only two possible parities for the first
element:

Case 1:

Assume parity of the first element is 0.

------------------------------------------------------------

Case 2:

Assume parity of the first element is 1.

------------------------------------------------------------

For each case,

1.

Compare the assumed parity with A[0].

If different,

one operation is required.

------------------------------------------------------------

2.

Using

next = current XOR B[j]

determine the required parity of the next element.

------------------------------------------------------------

3.

Compare the required parity with the actual parity of
A[j + 1].

If different,

one operation is required.

------------------------------------------------------------

4.

Continue until every element has been processed.

------------------------------------------------------------

The minimum operations among the two possible starting
parities is the answer.

------------------------------------------------------------

Why XOR?
--------

For modulo 2,

0 + 0 = 0

0 + 1 = 1

1 + 0 = 1

1 + 1 = 0

This is exactly the XOR truth table.

Hence,

(A[i] + A[i+1]) % 2

can be written as

Parity(A[i]) XOR Parity(A[i+1])

------------------------------------------------------------

Example:
--------

Input

A = [1,1,1]

B = [1,1]

------------------------------------------------------------

Assume first parity = 0

Required parities

0

0 XOR 1 = 1

1 XOR 1 = 0

Sequence

[0,1,0]

Differences from

[1,1,1]

Positions 1 and 3

Operations = 2

------------------------------------------------------------

Assume first parity = 1

Required parities

1

1 XOR 1 = 0

0 XOR 1 = 1

Sequence

[1,0,1]

Differences from

[1,1,1]

Only position 2

Operations = 1

Answer

1

------------------------------------------------------------

Why This Works:
---------------

The parity of every element depends only on the parity
of the previous element and the required XOR value.

Thus,

choosing the first parity completely determines the
entire sequence.

Since there are only two possible choices,

checking both guarantees the minimum number of
operations.

------------------------------------------------------------

Time Complexity:
----------------

O(N)

Two linear traversals of the array are performed.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few variables are used.

*/