#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    
    int count = 0;
    for(int i = 1; i < n - 1; i++) {
        if(a[i] > a[i- 1] && a[i] > a[i + 1]) count++;
    }
    
    cout << count << endl;
    return 0;
}

/*

Idea:
------
We need to count all positions

i

such that

A[i] < A[i+1] > A[i+2]

This means the middle element of every consecutive
3-element window must be strictly greater than both of
its neighbors.

Since the condition depends only on three consecutive
elements,

we simply examine every possible window of length

3.

------------------------------------------------------------

Key Observation:
----------------

For every valid index

i,

the required pattern is

Smaller < Larger > Smaller

In other words,

the middle element forms a

local peak.

Example

3 7 4

↓

3 < 7

and

7 > 4

Therefore,

this window satisfies the condition.

--------------------------------

Example

5 3 4

↓

5 > 3

The first condition already fails,

so this window is invalid.

------------------------------------------------------------

Algorithm:
----------

Step 1

Read the array.

------------------------------------------------------------

Step 2

Traverse every possible middle element.

The middle index can range from

1

to

N - 2

(0-based indexing),

since each middle element must have both a left and a
right neighbor.

------------------------------------------------------------

Step 3

For every index

i,

check whether

A[i] > A[i - 1]

and

A[i] > A[i + 1]

If both conditions are true,

increment the answer.

------------------------------------------------------------

Step 4

Print the final count.

------------------------------------------------------------

Why Does This Work?
-------------------

Every valid position corresponds to exactly one window of
three consecutive elements.

The middle element must be strictly greater than both
neighbors.

The algorithm checks this condition for every possible
middle element exactly once.

If the condition holds,

that window contributes one valid answer.

Otherwise,

it is ignored.

Since every possible window is examined,

all valid positions are counted exactly once.

------------------------------------------------------------

Example:
--------

Array

3 1 4 1 5 2

--------------------------------

Window

3 1 4

Middle = 1

1 > 3 ?

No

Not counted.

--------------------------------

Window

1 4 1

Middle = 4

4 > 1

4 > 1

Valid

Count = 1

--------------------------------

Window

4 1 5

Middle = 1

1 > 4 ?

No

--------------------------------

Window

1 5 2

Middle = 5

5 > 1

5 > 2

Valid

Count = 2

Final Answer = 2

------------------------------------------------------------

Example:
--------

Array

1 1 1 2 1

--------------------------------

Window

1 1 1

Middle is not strictly greater.

--------------------------------

Window

1 1 2

Middle is not greater than

2.

--------------------------------

Window

1 2 1

Middle = 2

2 > 1

2 > 1

Valid

Answer = 1

------------------------------------------------------------

Why Strict Comparison?
----------------------

The problem requires

A[i] < A[i+1]

and

A[i+1] > A[i+2]

Therefore,

equal values do not satisfy the condition.

For example,

2 2 1

is invalid because

2 < 2

is false.

Similarly,

1 2 2

is also invalid because

2 > 2

is false.

------------------------------------------------------------

Time Complexity:
----------------

The array is traversed once.

Each position performs only constant-time comparisons.

Time Complexity:

O(N)

------------------------------------------------------------

Space Complexity:
-----------------

Only a few variables are used besides the input array.

Auxiliary Space:

O(1)

(The input array itself requires O(N) storage.)

*/