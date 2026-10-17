#include<bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<char>> v(2, vector<char>(2));
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cin >> v[i][j];
        }
    }
    
    if(v[0][0] == 'A' && (v[0][1] == 'D' || v[1][0] == 'D')) {
         cout << "Yes\n";
         return 0;
    }
    if(v[0][1] == 'A' && (v[0][0] == 'D' || v[1][1] == 'D')) {
         cout << "Yes\n";
         return 0;
    }
    if(v[1][0] == 'A' && (v[0][0] == 'D' || v[1][1] == 'D')) {
         cout << "Yes\n";
         return 0;
    }
    if(v[1][1] == 'A' && (v[0][1] == 'D' || v[1][0] == 'D')) {
         cout << "Yes\n";
         return 0;
    }
    
    cout << "No\n";
    return 0;
}

/*
    Approach: Grid Traversal + Adjacent Cell Checking

    The goal is to determine whether the cells containing 'A' and 'D'
    are adjacent in a 2 x 2 grid.

    Two cells are adjacent if they share an edge. Diagonal cells do
    not count as adjacent.

    Since the grid has only 2 rows and 2 columns, we can directly
    check all possible positions of 'A' and verify whether 'D' is
    located in one of its adjacent cells.

    ------------------------------------------------------------
    Key Observation: Which cells are adjacent?
    ------------------------------------------------------------

    Consider a 2 x 2 grid:

        +---+---+
        | a | b |
        +---+---+
        | c | d |
        +---+---+

    The adjacent pairs are:

        a <-> b
        a <-> c
        b <-> d
        c <-> d

    These pairs share an edge.

    The diagonal pairs are:

        a <-> d
        b <-> c

    These pairs share only a corner, so they are NOT adjacent.

    Therefore, we need to check whether 'A' and 'D' occupy one of
    the four edge-sharing pairs.

    ------------------------------------------------------------
    Step 1: Read the grid
    ------------------------------------------------------------

        vector<vector<char>> v(2, vector<char>(2));

    We create a 2 x 2 character grid.

    `v[i][j]` represents the character at row `i` and column `j`,
    using 0-based indexing.

    The nested loops read all four characters:

        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                cin >> v[i][j];
            }
        }

    The outer loop visits the two rows, while the inner loop visits
    the two columns in each row.

    Example input:

        AB
        DC

    The grid becomes:

        v[0][0] = 'A'    v[0][1] = 'B'
        v[1][0] = 'D'    v[1][1] = 'C'

    ------------------------------------------------------------
    Step 2: Check whether A is at the top-left cell
    ------------------------------------------------------------

        if(v[0][0] == 'A' &&
           (v[0][1] == 'D' || v[1][0] == 'D'))

    If 'A' is at position `(0, 0)`, its adjacent cells are:

        Right -> (0, 1)
        Down  -> (1, 0)

    Therefore, 'D' must be in either `v[0][1]` or `v[1][0]`.

    If either condition is true, the cells share an edge.

    We print "Yes" and return immediately.

    ------------------------------------------------------------
    Step 3: Check whether A is at the top-right cell
    ------------------------------------------------------------

        if(v[0][1] == 'A' &&
           (v[0][0] == 'D' || v[1][1] == 'D'))

    If 'A' is at position `(0, 1)`, its adjacent cells are:

        Left  -> (0, 0)
        Down  -> (1, 1)

    We check whether 'D' occupies either of these positions.

    If it does, we print "Yes" and terminate the program.

    ------------------------------------------------------------
    Step 4: Check whether A is at the bottom-left cell
    ------------------------------------------------------------

        if(v[1][0] == 'A' &&
           (v[0][0] == 'D' || v[1][1] == 'D'))

    If 'A' is at position `(1, 0)`, its adjacent cells are:

        Up    -> (0, 0)
        Right -> (1, 1)

    We check whether 'D' is present in either cell.

    If so, the two cells share an edge, and the answer is "Yes".

    ------------------------------------------------------------
    Step 5: Check whether A is at the bottom-right cell
    ------------------------------------------------------------

        if(v[1][1] == 'A' &&
           (v[0][1] == 'D' || v[1][0] == 'D'))

    If 'A' is at position `(1, 1)`, its adjacent cells are:

        Up   -> (0, 1)
        Left -> (1, 0)

    If 'D' is in either of these positions, we print "Yes" and
    terminate the program.

    ------------------------------------------------------------
    Step 6: Handle the remaining case
    ------------------------------------------------------------

        cout << "No\n";

    If none of the four conditions succeeds, 'A' and 'D' are not
    adjacent.

    Since every possible position of 'A' has been checked, we can
    safely print "No".

    ------------------------------------------------------------
    Example 1
    ------------------------------------------------------------

    Input:

        AB
        DC

    Grid:

        A B
        D C

    'A' is at `(0, 0)`.

    Its right neighbor is 'B', and its bottom neighbor is 'D'.

    Since 'D' is directly below 'A', they share an edge.

    Output:

        Yes

    ------------------------------------------------------------
    Example 2
    ------------------------------------------------------------

    Input:

        AB
        CD

    Grid:

        A B
        C D

    'A' is at `(0, 0)`, while 'D' is at `(1, 1)`.

    These cells are diagonal from each other and share only a corner.

    Therefore, they are not adjacent.

    Output:

        No

    ------------------------------------------------------------
    Example 3
    ------------------------------------------------------------

    Input:

        BD
        CA

    Grid:

        B D
        C A

    'A' is at `(1, 1)`.

    Its upper neighbor is 'D', located at `(0, 1)`.

    Since 'D' is directly above 'A', they share an edge.

    Output:

        Yes

    ------------------------------------------------------------
    Correctness Intuition
    ------------------------------------------------------------

    In a 2 x 2 grid, every cell has exactly two adjacent cells.

    The solution checks all four possible positions of 'A' and
    identifies the two edge-sharing neighbors for each position.

    If 'D' occupies one of those neighbors, the solution prints "Yes".

    Otherwise, none of the possible adjacent relationships exists,
    so it prints "No".

    Thus, the solution correctly determines whether 'A' and 'D'
    are adjacent.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Time Complexity: O(1)

        Reading the grid takes constant time because it always
        contains exactly four characters.

        The solution then evaluates at most four conditions.

    Space Complexity: O(1)

        The grid always contains exactly four characters, so its
        storage does not grow with the input size.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Find the position of 'A' and check whether 'D' is in either
    of its two edge-sharing neighboring cells.

    If they share an edge, print "Yes"; otherwise, print "No".
*/