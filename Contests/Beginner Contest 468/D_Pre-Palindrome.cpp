#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.size();
    long long ans = 0;

    // Odd
    for (int i = 0; i < n; i++) {
        int l = i, r = i;
        int mismatch = 0;

        while (l >= 0 && r < n) {
            if (s[l] != s[r]) mismatch++;
            if (mismatch > 1) break;
            ans++;
            l--;
            r++;
        }
    }

    // Even
    for (int i = 0; i < n - 1; i++) {
        int l = i, r = i + 1;
        int mismatch = 0;

        while (l >= 0 && r < n) {
            if (s[l] != s[r]) mismatch++;
            if (mismatch > 1) break;
            ans++;
            l--;
            r++;
        }
    }

    cout << ans << endl;

    return 0;
}

/*

Idea:
------
A string can be converted into a palindrome by changing
at most one character

iff

the number of mismatched symmetric character pairs is
at most one.

Instead of generating every substring separately and
checking whether it is good,

we observe that every palindrome (or almost-palindrome)
has a center.

Therefore,

we expand around every possible center while keeping
track of the number of mismatched pairs encountered.

The moment the number of mismatches exceeds one,

no larger substring around the same center can ever be
made into a palindrome by changing only one character,
so we stop expanding.

This gives an efficient

Expand Around Center

solution.

------------------------------------------------------------

Key Observation:
----------------

Every substring belongs to exactly one of two categories:

1.

Odd Length

Example

abcba

Center

c

--------------------------------

2.

Even Length

Example

abccba

Center

between

c

and

c

Therefore,

checking every possible center guarantees that every
substring is considered exactly once.

------------------------------------------------------------

Mathematical Observation:
-------------------------

Consider a substring

S[l ... r]

When checking whether it can become a palindrome,

we only compare symmetric pairs.

Example

abcdef

Pairs compared are

(a,f)

(b,e)

(c,d)

Each unequal pair contributes exactly one mismatch.

If there are

k

mismatched pairs,

then

k

character modifications are required to convert the
substring into a palindrome,

because each mismatch can be fixed by changing one of
its two characters.

Therefore,

Substring is Good

⇔

Number of mismatched pairs ≤ 1

------------------------------------------------------------

Why Expansion Works:
--------------------

Suppose we are expanding from a center.

Initially,

Substring = center itself

(or two middle characters for even length).

Each expansion adds exactly one new symmetric pair.

Example

abcxcba

Expansion order

x

↓

c x c

↓

b c x c b

↓

a b c x c b a

Notice that during every expansion,

only one new pair

(S[l], S[r])

is introduced.

So,

we simply compare these two characters.

If they are different,

increment the mismatch count.

------------------------------------------------------------

Stopping Condition:
-------------------

Suppose during expansion,

Mismatch Count = 2

This means two different symmetric pairs already differ.

Since changing one character can repair only one pair,

every larger substring containing these two mismatches
will still require at least two changes.

Therefore,

all further expansions are guaranteed to be invalid.

So we immediately stop expanding.

This pruning is what makes the algorithm efficient.

------------------------------------------------------------

Algorithm:
----------

Step 1

Initialize

answer = 0

------------------------------------------------------------

Step 2

Process every possible

Odd Length

center.

For every index

i

Set

l = i

r = i

mismatch = 0

Expand outward while

• indices remain inside the string

• mismatch ≤ 1

Whenever

S[l] != S[r]

increment

mismatch.

If

mismatch > 1

stop expanding.

Otherwise,

the current substring is good,

so increment the answer.

------------------------------------------------------------

Step 3

Process every possible

Even Length

center.

For every adjacent pair

(i, i+1)

Set

l = i

r = i+1

Again expand outward using exactly the same logic.

------------------------------------------------------------

Step 4

Return the total count.

------------------------------------------------------------

Example:
--------

S = "ababa"

--------------------------------

Odd Centers

Center = 0

"a"

Good

--------------------------------

Center = 1

"b"

Good

"aba"

Good

--------------------------------

Center = 2

"a"

Good

"bab"

Good

"ababa"

Good

--------------------------------

Continue similarly for all centers.

------------------------------------------------------------

Even Centers

Center between

a

and

b

Substring

"ab"

Mismatch = 1

Still Good

Expand

"baba"

Now mismatches become

2

Stop.

The same process is repeated for every even center.

------------------------------------------------------------

Why Does This Work?
-------------------

Every substring has a unique center.

By expanding around every odd and even center,

every possible substring is visited exactly once.

During expansion,

the mismatch count always represents the number of
symmetric pairs that differ.

If the mismatch count is

0,

the substring is already a palindrome.

If the mismatch count is

1,

changing one character is sufficient to make it a
palindrome.

If the mismatch count becomes

2,

at least two character changes are required,

making the substring invalid.

Thus,

every good substring is counted exactly once,

and every invalid substring is discarded immediately.

------------------------------------------------------------

Time Complexity:
----------------

There are

n

odd centers

and

n - 1

even centers.

For each center,

the expansion may extend at most

O(n)

characters.

Worst-case Time Complexity:

O(n²)

------------------------------------------------------------

Space Complexity:
-----------------

Only a few variables are maintained during expansion.

No additional data structures are used.

Space Complexity:

O(1)

*/