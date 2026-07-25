#include <bits/stdc++.h>
using namespace std;

int main() {
    long long H, W;
    cin >> H >> W;

    cout << (W * 10000 >= 25 * H * H ? "Yes\n" : "No\n");
}

/*

Idea:
------
BMI is calculated as

BMI = Weight(kg) / Height(m)^2

The given height is in centimeters, so first convert it
to meters.

Instead of performing floating-point division, rearrange
the inequality using integer arithmetic.

------------------------------------------------------------

Derivation:
-----------

Height in meters

= H / 100

BMI

= W / (H / 100)^2

= W / (H^2 / 10000)

= (W × 10000) / H^2

A person is considered obese if

BMI >= 25

Therefore,

(W × 10000) / H^2 >= 25

Multiplying both sides by H^2 gives

W × 10000 >= 25 × H × H

Now only integer multiplication is required.

------------------------------------------------------------

Algorithm:
----------

1.

Read H (height in cm) and W (weight in kg).

2.

Check whether

W * 10000 >= 25 * H * H

3.

If true,

print "Yes".

Otherwise,

print "No".

------------------------------------------------------------

Example:
--------

Input:

H = 180

W = 60

Left Side

60 × 10000 = 600000

Right Side

25 × 180 × 180 = 810000

Since

600000 < 810000

Output:

No

------------------------------------------------------------

Example:

H = 180

W = 81

Left Side

81 × 10000 = 810000

Right Side

25 × 180 × 180 = 810000

Since

810000 >= 810000

Output:

Yes

------------------------------------------------------------

Why long long?
--------------

Although the given constraints are small,

using long long ensures that the multiplication

25 × H × H

and

W × 10000

cannot overflow if the constraints were larger.

------------------------------------------------------------

Time Complexity:
----------------

O(1)

Only a constant number of arithmetic operations are
performed.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few variables are used.

*/