#include<bits/stdc++.h>
using namespace std;

int main() {
    int m, d;
    cin >> m >> d;
    
    string s;
    cin >> s;
    
    vector<bool> watched(m, false);
    for(int i = 0; i < m ; i++) {
        if(s[i] == 'G') {
            int start = (i - d >= 0) ? i - d : 0;
            int end = min(m, i + d + 1);
            for(int j = start; j < end; j++) watched[j] = true;
        }
    }
    
    int count = 0;
    for(auto x : watched) if(x == false) count++;
    
    cout << count << endl;
    return 0;
}

/*

Idea:
------
Every guard watches all cells whose distance from it is at
most

D.

Therefore,

for every guard,

we simply mark every cell lying in the interval

[guardPosition - D, guardPosition + D]

as watched.

After processing all guards,

the cells that were never marked are exactly the cells
that are not watched.

------------------------------------------------------------

Key Observation:
----------------

Suppose a guard stands at position

i.

A cell

x

is watched if

|x - i| ≤ D

This inequality can be rewritten as

i - D ≤ x ≤ i + D

Therefore,

every guard watches one continuous interval around its
position.

So for each guard,

we simply mark every index inside this interval.

------------------------------------------------------------

Algorithm:
----------

Step 1

Create a boolean array

watched[]

of size

M,

initially filled with

false.

watched[i] = true

means that cell

i

is watched by at least one guard.

------------------------------------------------------------

Step 2

Traverse the string.

Whenever

S[i] == 'G'

a guard is found.

------------------------------------------------------------

Step 3

Compute the interval watched by this guard.

Left boundary

start = max(0, i - D)

Right boundary

end = min(M, i + D + 1)

The upper bound is written as

i + D + 1

because the loop uses

j < end.

------------------------------------------------------------

Step 4

Mark every cell inside this interval.

For every

j

from

start

to

end - 1

Set

watched[j] = true

Even if multiple guards watch the same cell,

assigning

true

again has no effect.

------------------------------------------------------------

Step 5

After processing every guard,

count all indices whose value is still

false.

These are exactly the unwatched cells.

------------------------------------------------------------

Why Does This Work?
-------------------

Each guard watches every cell whose distance from it is
at most

D.

The algorithm explicitly marks every such cell.

If multiple guards watch the same cell,

it is simply marked

true

again,

which is harmless.

Since every guard is processed,

every watched cell is marked.

Conversely,

if a cell remains

false,

then no guard's watching interval contains that cell,

meaning it is not watched by anyone.

Thus,

counting all

false

entries gives the correct answer.

------------------------------------------------------------

Example:
--------

M = 7

D = 1

S =

".G...GG"

Indices

0 1 2 3 4 5 6

--------------------------------

Guard at index

1

Watches

[0,2]

watched

T T T F F F F

--------------------------------

Guard at index

5

Watches

[4,6]

watched

T T T F T T T

--------------------------------

Guard at index

6

Watches

[5,6]

Already marked.

Final watched array

T T T F T T T

Only index

3

remains

false.

Answer = 1

------------------------------------------------------------

Example:
--------

M = 6

D = 5

S =

"......"

There are no guards.

No cell is ever marked.

watched

F F F F F F

Answer = 6

------------------------------------------------------------

Why Boundary Checks Are Needed?
-------------------------------

Suppose a guard stands near the beginning.

Example

i = 1

D = 3

Then

i - D

becomes negative.

Since negative indices are invalid,

we clamp it to

0.

Similarly,

if

i + D

extends beyond the last cell,

we clamp it to

M - 1

(using

min(M, i + D + 1)

for the exclusive upper bound).

This ensures that every accessed index is valid.

------------------------------------------------------------

Time Complexity:
----------------

Let

G

be the number of guards.

Each guard marks at most

2D + 1

cells.

Worst-case Time Complexity:

O(M × (2D + 1))

Since

M ≤ 100,

this easily fits within the constraints.

In the worst case,

D ≈ M,

giving

O(M²).

------------------------------------------------------------

Space Complexity:
-----------------

The boolean array

watched

stores one value for every cell.

Space Complexity:

O(M)

*/