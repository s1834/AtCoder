#include<bits/stdc++.h>
using namespace std;

int main() {
    vector<string> v;
    
    for(int i = 0; i < 5; i++) {
        string s;
        cin >> s;
        v.push_back(s);
    }
    
    int ans = 0;
    for(int i = 0; i < 5; i++) {
        int count = 0;
        for(int j = 0; j < 5; j++) {
            if(v[i][j] == 'o') count++;
        }
        ans = max(ans, count);
    }
    
     for(int i = 0; i < 5; i++) {
        int count = 0;
        for(int j = 0; j < 5; j++) {
            if(v[j][i] == 'o') count++;
        }
        ans = max(ans, count);
    }
    
    int count = 0;
    for(int i = 0; i < 5; i++) {
        if(v[i][i] == 'o') count++;
    }
    ans = max(ans, count);
    
    int n = 4;
    count = 0;
    for(int i = 0; i < 5; i++) {
        if(v[i][n] == 'o') count++;
        n--;
    }
    
    ans = max(ans, count);
    
    cout << 5 - ans << endl;
    
    return 0;
}

/*
Approach: Brute Force + Counting Marks in All Possible Lines

Intuition:
----------
We are given a 5 x 5 grid where:
- 'o' represents a marked cell.
- '.' represents an unmarked cell.

We need to achieve a bingo by having all 5 cells marked in at
least one horizontal, vertical, or diagonal line.

Since we can add marks to any unmarked cells, the minimum number
of additional marks required for a particular line is:

5 - (number of already marked cells in that line)

To minimize the additional marks, we need to choose the line
that already contains the maximum number of marked cells.

Therefore, we calculate the maximum number of 'o' characters
among all rows, columns, and both diagonals.

The final answer is:

5 - maximum marked cells in any valid line.

--------------------------------------------------
1. Read the Grid
--------------------------------------------------

vector<string> v;

for(int i = 0; i < 5; i++) {
    string s;
    cin >> s;
    v.push_back(s);
}

Read the 5 rows of the grid and store them in a vector of strings.

Each character represents whether a cell is marked or unmarked.

--------------------------------------------------
2. Initialize the Answer
--------------------------------------------------

int ans = 0;

ans stores the maximum number of already marked cells found
in any valid bingo line.

We initially set it to 0.

--------------------------------------------------
3. Count Marked Cells in Every Row
--------------------------------------------------

for(int i = 0; i < 5; i++) {
    int count = 0;

    for(int j = 0; j < 5; j++) {
        if(v[i][j] == 'o') count++;
    }

    ans = max(ans, count);
}

The outer loop selects each row.

The inner loop traverses all five columns of that row.

Whenever v[i][j] == 'o', increment count.

After processing a row, update ans with the maximum number
of marked cells found so far.

This checks all 5 horizontal bingo possibilities.

--------------------------------------------------
4. Count Marked Cells in Every Column
--------------------------------------------------

for(int i = 0; i < 5; i++) {
    int count = 0;

    for(int j = 0; j < 5; j++) {
        if(v[j][i] == 'o') count++;
    }

    ans = max(ans, count);
}

Here, the outer loop selects each column.

The inner loop traverses all five rows of that column.

Notice the indexing:

v[j][i]

- j represents the row.
- i represents the fixed column.

Count the marked cells in each column and update ans.

This checks all 5 vertical bingo possibilities.

--------------------------------------------------
5. Count Marked Cells in the Main Diagonal
--------------------------------------------------

int count = 0;

for(int i = 0; i < 5; i++) {
    if(v[i][i] == 'o') count++;
}

The main diagonal consists of cells where row and column
indices are equal:

(0,0), (1,1), (2,2), (3,3), (4,4)

Count all marked cells on this diagonal.

ans = max(ans, count);

Update ans if the main diagonal contains more marked cells
than the previously checked rows or columns.

--------------------------------------------------
6. Count Marked Cells in the Anti-Diagonal
--------------------------------------------------

int n = 4;
count = 0;

for(int i = 0; i < 5; i++) {
    if(v[i][n] == 'o') count++;
    n--;
}

The anti-diagonal consists of cells:

(0,4), (1,3), (2,2), (3,1), (4,0)

Here:
- i moves from the first row to the last row.
- n starts at the last column (4) and decreases after each iteration.

This allows us to traverse the anti-diagonal.

Count the marked cells and update ans:

ans = max(ans, count);

--------------------------------------------------
7. Calculate the Minimum Additional Marks
--------------------------------------------------

cout << 5 - ans << endl;

Every bingo line contains exactly 5 cells.

Since ans represents the maximum number of cells already marked
in any valid line, the minimum additional marks required are:

5 - ans

Choosing the line with the most existing marks minimizes
the number of new marks needed.

--------------------------------------------------
8. Example Walkthrough
--------------------------------------------------

Consider:

.o..o
..oo.
.o..o
o.o..
o..oo

We examine:
- All 5 rows.
- All 5 columns.
- Main diagonal.
- Anti-diagonal.

Suppose the maximum number of marked cells found in any one
of these lines is 3.

Then:

ans = 3

Minimum additional marks:

5 - 3 = 2

Output: 2

We only need to mark the remaining two cells in that line
to achieve bingo.

--------------------------------------------------
9. Why the Algorithm Works
--------------------------------------------------

A bingo requires all 5 cells of at least one valid line to
be marked.

For any particular line, the number of additional marks
required is exactly 5 minus its existing marked-cell count.

Therefore, minimizing additional marks is equivalent to
maximizing the number of already marked cells in a line.

The algorithm checks every possible bingo line:
- 5 horizontal rows.
- 5 vertical columns.
- 2 diagonals.

It stores the maximum marked-cell count in ans.

Thus, 5 - ans gives the minimum number of additional marks
required to achieve bingo.

--------------------------------------------------
10. Complexity Analysis
--------------------------------------------------

Time Complexity: O(1)

The grid is always 5 x 5, so the algorithm performs a fixed
number of operations.

More generally, for an N x N grid, the time complexity is O(N^2).

Space Complexity: O(1)

The grid uses a fixed 5 x 5 size, and only a few counter
variables are used in addition to the input storage.

Core Idea:
----------
Count the number of marked cells in every row, column, and
both diagonals. Find the maximum count and subtract it from
5 to get the minimum additional marks needed.
*/