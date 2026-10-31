#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 0; i < n; i++) {
        long long ans = LLONG_MAX;

        // infect right neighbor first
        if (i + 1 < n) {
            long long left = (x[i + 1] - x[0]) / 2;
            long long right = (x[n - 1] - x[i]) / 2;

            ans = min(ans, max(left, right));
        }

        // infect left neighbor first
        if (i - 1 >= 0) {
            long long left = (x[i] - x[0]) / 2;
            long long right = (x[n - 1] - x[i - 1]) / 2;

            ans = min(ans, max(left, right));
        }

        cout << ans << '\n';
    }

    return 0;
}

/*
Approach: Greedy + Two Possible Infection Directions + Minimax

Intuition:
----------
We have n people standing on a number line at sorted coordinates:

x[0] < x[1] < ... < x[n-1]

Initially, person i becomes a zombie, and everyone else is human.

Zombies and humans can move at speed at most 1. Whenever a zombie
meets a human, that human becomes a zombie.

The goal is to find the minimum time required to infect everyone
for each possible starting person.

The key observation is that infection can spread in two directions
along the number line:
- From left to right.
- From right to left.

Since the initial zombie is at position i, we consider two possible
strategies:

1. Infect the right neighbor first.
2. Infect the left neighbor first.

For each strategy, calculate the time needed to cover the leftmost
and rightmost parts of the line.

The total required time is the maximum of these two times because
both sides must be completely infected.

Finally, choose the minimum among the two strategies.

--------------------------------------------------
1. Read Input
--------------------------------------------------

int n;
cin >> n;

vector<long long> x(n);

for (int i = 0; i < n; i++)
    cin >> x[i];

Store the coordinates of all people.

The problem guarantees that coordinates are already given in
increasing order, so no sorting is required.

long long is used because coordinates and calculated distances
can be large.

--------------------------------------------------
2. Handle the Single-Person Case
--------------------------------------------------

if (n == 1) {
    cout << 0 << '\n';
    return 0;
}

If there is only one person, that person is already a zombie
at time 0.

There are no other people to infect.

Therefore, the answer is 0.

--------------------------------------------------
3. Calculate the Answer for Every Starting Person
--------------------------------------------------

for (int i = 0; i < n; i++) {

    long long ans = LLONG_MAX;

Fix person i as the initial zombie.

ans stores the minimum infection time among the two strategies.

Initially, set it to LLONG_MAX because we will minimize it.

--------------------------------------------------
4. Strategy 1: Infect the Right Neighbor First
--------------------------------------------------

if (i + 1 < n) {

This strategy is possible only if person i has a right neighbor.

long long left = (x[i + 1] - x[0]) / 2;

Calculate the time required to cover the left portion of the
number line after the infection starts by moving toward the
right neighbor.

The distance considered is:

x[i + 1] - x[0]

Since the two sides can be covered through movement at speed 1,
the corresponding time is half this distance.

long long right = (x[n - 1] - x[i]) / 2;

Calculate the time required to cover the right portion.

The distance considered is:

x[n - 1] - x[i]

Again, divide by 2 to obtain the required time.

ans = min(ans, max(left, right));

Both portions must be completely infected.

Therefore, the time for this strategy is determined by the
slower of the two sides:

max(left, right)

Update ans with the minimum of the current answer and this
strategy's required time.

--------------------------------------------------
5. Strategy 2: Infect the Left Neighbor First
--------------------------------------------------

if (i - 1 >= 0) {

This strategy is possible only if person i has a left neighbor.

long long left = (x[i] - x[0]) / 2;

Calculate the time required to cover the left portion.

The distance considered is:

x[i] - x[0]

Divide it by 2 to obtain the corresponding time.

long long right = (x[n - 1] - x[i - 1]) / 2;

Calculate the time required to cover the right portion.

The distance considered is:

x[n - 1] - x[i - 1]

Again, divide it by 2.

ans = min(ans, max(left, right));

Both sides must be completely infected, so take the maximum
of their required times.

Then minimize ans using this second strategy.

--------------------------------------------------
6. Print the Answer
--------------------------------------------------

cout << ans << '\n';

After evaluating both possible strategies, ans contains the
minimum infection time for the initial zombie at position i.

Print the answer for this starting person.

The outer loop repeats this calculation for every person.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Input:
n = 5

x = [2, 4, 10, 14, 18]

Consider person i = 2, located at coordinate 10.

Strategy 1: Infect Right Neighbor First
---------------------------------------

left = (x[3] - x[0]) / 2
     = (14 - 2) / 2
     = 6

right = (x[4] - x[2]) / 2
      = (18 - 10) / 2
      = 4

Required time:

max(6, 4) = 6

Strategy 2: Infect Left Neighbor First
--------------------------------------

left = (x[2] - x[0]) / 2
     = (10 - 2) / 2
     = 4

right = (x[4] - x[1]) / 2
      = (18 - 4) / 2
      = 7

Required time:

max(4, 7) = 7

Choose the minimum:

ans = min(6, 7) = 6

Therefore, when person 3 is initially a zombie, the minimum
infection time calculated by this implementation is 6.

--------------------------------------------------
8. Why the Greedy Strategy Works
--------------------------------------------------

The initial zombie can begin spreading infection in either
direction.

The two cases represent the possible choices of which neighboring
person is infected first.

For each choice:
- The left portion has a corresponding coverage time.
- The right portion has a corresponding coverage time.
- Both portions must be completely infected.

Therefore, the total time for a strategy is the maximum of the
two required times.

Since either strategy can be selected, we take the minimum
of their maximum times.

This gives the minimum among the two candidate strategies
considered by the implementation.

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

- Reading the coordinates takes O(n).
- The outer loop processes each person once.
- Each person performs at most two constant-time calculations.

Therefore, the overall time complexity is O(n).

Space Complexity: O(n)

The coordinate array x stores n elements.

Apart from the input array, the algorithm uses only a constant
amount of additional space.

Core Idea:
----------
For every possible initial zombie, evaluate two strategies:
infect the right neighbor first or infect the left neighbor first.
For each strategy, take the maximum of the left and right coverage
times, then choose the minimum of the two candidate times.
*/