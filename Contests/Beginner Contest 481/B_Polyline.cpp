#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
   
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    
    int count = 0;
    for (int i = 0; i < n; i++) if (a[i] == k) count++;

    for (int i = 0; i < n - 1; i++) if ((a[i] < k && a[i + 1] > k) || (a[i] > k && a[i + 1] < k)) count++;
  
    cout << count << endl;
    
    return 0;
}

/*
Approach: Count Vertices + Count Segment Crossings

Intuition:
----------
We are given a polyline formed by connecting consecutive points.
Each point has a y-coordinate, and we need to count the distinct
points on the polyline whose y-coordinate equals k.

The polyline consists of:
1. Its original vertices.
2. Points lying inside line segments that cross the horizontal line y = k.

We count both cases separately.

1. Count Vertices on y = k
--------------------------
int count = 0;

for(int i = 0; i < n; i++)
    if(a[i] == k) count++;

Every original point whose y-coordinate equals k contributes one
point to the answer.

2. Count Crossings Between Consecutive Vertices
-----------------------------------------------
for(int i = 0; i < n - 1; i++)

Each segment connects points i and i + 1.

A segment crosses the horizontal line y = k strictly inside the
segment if one endpoint lies below k and the other lies above k.

Condition:
(a[i] < k && a[i + 1] > k) ||
(a[i] > k && a[i + 1] < k)

If this condition is true, the segment contains exactly one point
whose y-coordinate is k, so we increment count.

We use strict inequalities because endpoints with y-coordinate k
have already been counted in the first loop.

3. Why We Avoid Double Counting
-------------------------------
If a vertex has y-coordinate k, it may be shared by two consecutive
segments. Counting vertices separately ensures that this shared
endpoint contributes only once.

The second loop counts only crossings strictly inside segments,
so it never counts a vertex already included in the first loop.

The constraints guarantee that the number of qualifying points
is finite, so segments lying entirely on y = k do not occur.

4. Example Walkthrough
----------------------
n = 5, k = 3
a = [1, 3, 1, 5, 1]

First loop: Count vertices with y = 3.
- a[1] = 3, so count = 1.

Second loop: Check consecutive segments.

Segment 0 -> 1: 1 to 3
- Endpoint reaches k, so no strict crossing is counted.

Segment 1 -> 2: 3 to 1
- Endpoint reaches k, so no strict crossing is counted.

Segment 2 -> 3: 1 to 5
- 1 < 3 < 5, so count = 2.

Segment 3 -> 4: 5 to 1
- 5 > 3 > 1, so count = 3.

Output: 3

The three points are the vertex at y = 3 and the two interior
segment crossings.

5. Complexity Analysis
----------------------
Time Complexity: O(n)
- The first loop visits all n vertices.
- The second loop visits n - 1 segments.

Space Complexity: O(n)
- The array a stores the y-coordinates of all vertices.
- The counting logic itself uses O(1) additional space.

Core Idea:
----------
Count every vertex whose y-coordinate equals k, then count every
segment whose endpoints lie strictly on opposite sides of k.
This counts all qualifying points without double-counting shared
vertices.
*/