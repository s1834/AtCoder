#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, t;
    cin >> n >> k >> t;

    vector<int> aoki(n);
    for(int i = 0; i < n; i++) cin >> aoki[i];

    sort(aoki.begin(), aoki.end());

    int start = 0;
    int end = 0;
    int presses = 0;

    for(int i = 0; i < n; i++) {
        if(aoki[i] > t) break;
        while(end < aoki[i]) {
            presses++;
            end += k;
        }
        end = max(end, aoki[i] + k);
    }

    while(end < t) {
        presses++;
        end += k;
    }

    cout << presses << endl;

    return 0;
}

/*
Approach: Greedy Simulation After Sorting

Intuition:
----------
The shower stays on for k seconds after each button press. If the button
is pressed at time x, hot water continues flowing until time x + k,
including the exact endpoint.

We need to count the minimum number of additional presses Takahashi must
make so that hot water is continuously available from time 0 to time t,
while also accounting for the presses made by the Aokis.

Key Idea:
---------
Sort all Aoki press times in increasing order.

Maintain:
- end: the time until which hot water is currently guaranteed to flow.
- presses: the total number of button presses made by Takahashi.
- k: the duration for which each press keeps the shower running.

Process each Aoki's press time:
1. If the Aoki presses after time t, stop processing because that press
   cannot help cover the required interval [0, t].
2. While end is earlier than the Aoki's press time, Takahashi must press
   the button to extend the hot-water interval.
3. After reaching the Aoki's press time, update end to the later of
   its current value and aoki[i] + k, because the Aoki's press also
   keeps the shower running for k seconds.

Finally, if hot water does not yet reach time t, keep pressing the
button until end reaches or exceeds t.

Step-by-Step Code Explanation:
------------------------------

1. Read the input:
   n = number of Aokis
   k = duration of hot water after each press
   t = final time until which hot water must be available

   The array aoki stores the times at which the Aokis press the button.

2. Sort the press times:
   sort(aoki.begin(), aoki.end());

   Processing press times chronologically allows us to extend the
   current hot-water interval without revisiting earlier events.

3. Initialize the variables:
   start = 0;
   end = 0;
   presses = 0;

   Initially, no hot-water interval has been established, so end = 0.
   presses counts only the presses made by Takahashi.

   Note: start is declared in the code but never used.

4. Process each Aoki's press:
   for(int i = 0; i < n; i++)

   If aoki[i] > t, the loop breaks because this press occurs after the
   required interval ends.

   Otherwise, execute:

   while(end < aoki[i]) {
       presses++;
       end += k;
   }

   If end is earlier than the next Aoki's press time, Takahashi must
   press the button again to extend the interval. Each such press
   extends end by k seconds.

   Once end reaches or passes aoki[i], the Aoki's press can contribute
   to keeping the shower running. Update:

   end = max(end, aoki[i] + k);

   This ensures that the covered interval extends at least until
   aoki[i] + k, without shortening any interval already covered.

5. Cover the remaining interval:
   while(end < t) {
       presses++;
       end += k;
   }

   After all relevant Aoki press times have been processed, hot water
   may still stop before time t. Takahashi continues pressing the button
   until end reaches or exceeds t.

6. Print the answer:
   cout << presses << endl;

   The answer is the total number of additional presses made by
   Takahashi during the simulation.

Example Walkthrough:
--------------------
Suppose:
n = 3, k = 4, t = 20
aoki = [6, 7, 12]

The press times are already sorted.

Initially:
end = 0, presses = 0

Aoki presses at time 6:
- end = 0 < 6, so Takahashi presses:
  presses = 1, end = 4
- end = 4 < 6, so Takahashi presses again:
  presses = 2, end = 8
- Since end >= 6, the Aoki's press is covered.
- Update end = max(8, 6 + 4) = 10.

Aoki presses at time 7:
- end = 10, which is already beyond time 7.
- Update end = max(10, 7 + 4) = 11.

Aoki presses at time 12:
- end = 11 < 12, so Takahashi presses:
  presses = 3, end = 15
- Now end >= 12.
- Update end = max(15, 12 + 4) = 16.

Cover the remaining interval until time 20:
- end = 16 < 20, so Takahashi presses:
  presses = 4, end = 20
- The required interval is now covered.

Output: 4

Why the Greedy Approach Works:
------------------------------
At each step, Takahashi presses only when the currently covered interval
ends before the next Aoki's press time. Without another press, there
would be a gap with no hot water.

Each Aoki's press extends the covered interval to at least aoki[i] + k.
Taking the maximum with the existing end preserves any coverage that
already extends further.

After processing the Aokis, the final loop extends coverage until time t.
Thus, the simulation adds presses exactly when needed to prevent gaps
and reach the required endpoint.

Complexity Analysis:
--------------------
Let n be the number of Aokis.

Time Complexity: O(n log n + n + p), where p is the number of additional
presses made by Takahashi. Sorting takes O(n log n), and each Aoki is
processed once. The while loops collectively perform p iterations.

Space Complexity: O(n) for storing the Aoki press times.

Core Idea:
----------
Sort the Aoki press times, track the endpoint of the current hot-water
interval, and add a Takahashi press whenever that interval ends before
the next Aoki press or before the final time t.
*/