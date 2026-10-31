#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w, n, q;
    cin >> h >> w >> n >> q;

    vector<int> row(n), col(n);

    for (int i = 0; i < n; i++) cin >> row[i] >> col[i];

    sort(row.begin(), row.end());
    sort(col.begin(), col.end());

    while (q--) {
        int x, a, b;
        cin >> x >> a >> b;

        if (x == 1) {
            auto l = lower_bound(row.begin(), row.end(), a);
            auto r = upper_bound(row.begin(), row.end(), b);

            cout << r - l << endl;
        } else {
            auto l = lower_bound(col.begin(), col.end(), a);
            auto r = upper_bound(col.begin(), col.end(), b);

            cout << r - l << endl;
        }
    }

    return 0;
}

/*
Approach: Sorting + Binary Search

Intuition:
----------
We are given N pieces placed on an H x W grid.

We need to answer two types of queries:

1. Count the number of pieces placed in rows from u to d.
2. Count the number of pieces placed in columns from l to r.

Since H and W can be as large as 10^9, creating a frequency
array for every row or column would be inefficient.

Instead, we store only the coordinates where pieces actually exist.

The key idea is:
- Store all row coordinates in one array.
- Store all column coordinates in another array.
- Sort both arrays.
- Use binary search to count coordinates within a given range.

--------------------------------------------------
1. Read Input
--------------------------------------------------

int h, w, n, q;
cin >> h >> w >> n >> q;

Read:
- h = Number of rows.
- w = Number of columns.
- n = Number of pieces.
- q = Number of queries.

vector<int> row(n), col(n);

Create two arrays:
- row stores the row coordinate of every piece.
- col stores the column coordinate of every piece.

for (int i = 0; i < n; i++)
    cin >> row[i] >> col[i];

Read the coordinates of all N pieces.

For every piece at (R[i], C[i]):
- Store R[i] in row[i].
- Store C[i] in col[i].

--------------------------------------------------
2. Sort Row and Column Coordinates
--------------------------------------------------

sort(row.begin(), row.end());
sort(col.begin(), col.end());

Sort both coordinate arrays independently.

Why do we sort them?

Binary search requires a sorted array.

After sorting:
- row contains all piece row coordinates in ascending order.
- col contains all piece column coordinates in ascending order.

This allows us to efficiently count how many coordinates
belong to any given inclusive range.

Notice that we do not need to store the complete grid.
We only store the coordinates of the N pieces.

--------------------------------------------------
3. Process Queries
--------------------------------------------------

while (q--) {

    int x, a, b;
    cin >> x >> a >> b;

Each query contains:
- x = Query type.
- a = Starting row or column.
- b = Ending row or column.

Since the query type determines which coordinate array
we need to search, we handle the two cases separately.

--------------------------------------------------
4. Type 1: Count Pieces in Rows [a, b]
--------------------------------------------------

if (x == 1) {

For a type 1 query, we need to count all pieces whose row
coordinates lie in the inclusive range [a, b].

Find the First Valid Position
----------------------------

auto l = lower_bound(row.begin(), row.end(), a);

lower_bound() returns an iterator pointing to the first element
that is greater than or equal to a.

Therefore, l represents the first piece whose row coordinate
is at least a.

Find the Position After the Last Valid Element
-----------------------------------------------

auto r = upper_bound(row.begin(), row.end(), b);

upper_bound() returns an iterator pointing to the first element
strictly greater than b.

Therefore, r represents the position immediately after the
last piece whose row coordinate is at most b.

Calculate the Count
-------------------

cout << r - l << endl;

The difference between these two iterators gives the number
of elements in the inclusive range [a, b].

This works because:

lower_bound(a) gives the first valid element.
upper_bound(b) gives the position after the last valid element.

Hence:

Count = upper_bound(b) - lower_bound(a)

--------------------------------------------------
5. Type 2: Count Pieces in Columns [a, b]
--------------------------------------------------

else {

For a type 2 query, we need to count all pieces whose column
coordinates lie in the inclusive range [a, b].

The same binary search technique is applied to the col array.

Find the First Valid Position
----------------------------

auto l = lower_bound(col.begin(), col.end(), a);

Find the first column coordinate greater than or equal to a.

Find the Position After the Last Valid Element
-----------------------------------------------

auto r = upper_bound(col.begin(), col.end(), b);

Find the first column coordinate strictly greater than b.

Calculate the Count
-------------------

cout << r - l << endl;

The difference gives the number of pieces whose column
coordinates belong to the inclusive range [a, b].

--------------------------------------------------
6. Why lower_bound() and upper_bound()?
--------------------------------------------------

Suppose:

row = [1, 2, 2, 4, 5, 7]

Query:
a = 2
b = 5

lower_bound(row.begin(), row.end(), 2)
points to the first occurrence of 2.

upper_bound(row.begin(), row.end(), 5)
points to the first element greater than 5, which is 7.

The elements between these iterators are:

[2, 2, 4, 5]

Their count is:

r - l = 4

This correctly includes both boundaries and handles duplicate
coordinates.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Input:

h = 5, w = 7, n = 5

Pieces:
(1, 1)
(2, 3)
(2, 5)
(4, 3)
(5, 7)

After extracting coordinates:

row = [1, 2, 2, 4, 5]
col = [1, 3, 5, 3, 7]

After sorting:

row = [1, 2, 2, 4, 5]
col = [1, 3, 3, 5, 7]

Query 1:
1 2 4

Count pieces in rows [2, 4].

Valid row coordinates:
[2, 2, 4]

Answer = 3

Query 2:
2 3 5

Count pieces in columns [3, 5].

Valid column coordinates:
[3, 3, 5]

Answer = 3

Query 3:
1 3 3

Count pieces in row 3.

No piece exists in row 3.

Answer = 0

--------------------------------------------------
8. Why the Algorithm Works
--------------------------------------------------

1. Every piece contributes exactly one entry to the row array
   and one entry to the column array.

2. Sorting ensures that equal coordinates are grouped together
   and all coordinates are in ascending order.

3. For a query [a, b], lower_bound(a) identifies the first
   coordinate that satisfies the lower boundary.

4. upper_bound(b) identifies the position immediately after
   the last coordinate satisfying the upper boundary.

5. Subtracting the iterators gives the exact number of pieces
   in the requested inclusive range.

Therefore, both query types are answered correctly without
constructing or traversing the entire grid.

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Let N be the number of pieces and Q be the number of queries.

Preprocessing:
--------------

Reading coordinates takes O(N).

Sorting row and col independently takes:

O(N log N)

Each Query:
-----------

Each query performs:
- One lower_bound(): O(log N)
- One upper_bound(): O(log N)

Therefore, each query takes O(log N).

For Q queries:

O(Q log N)

Overall Time Complexity:

O(N log N + Q log N)

Space Complexity:

O(N)

We maintain two arrays of size N:
- row
- col

No additional memory proportional to H or W is required.

Core Idea:
----------
Store and independently sort all row and column coordinates.
For every query [a, b], use:

upper_bound(b) - lower_bound(a)

to count the coordinates within the inclusive range efficiently.
*/